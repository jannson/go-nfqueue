#include <sys/socket.h>
#include <sys/time.h> /* timeval */
#include <arpa/inet.h>
#include <linux/netfilter.h>
#include <libnetfilter_queue/libnetfilter_queue.h>

#define NFQ_NUM 4
#define QUEUE_MAXLEN 4096

//gcc nfq_demo.c -o nfq_demo -lnfnetlink -lnetfilter_queue

static int nfq_cb(struct nfq_q_handle *qh, struct nfgenmsg *msg, struct nfq_data *nfa, void *data) {
    return 0;
}

int nfq_demo(void) {
    struct nfq_handle *h = nfq_open();
    if (!h) {
        return -1;
    }

    /* here, failed on nfq_unbind_pf */
    if (nfq_unbind_pf(h, AF_INET) < 0) {
        printf("nfq_unbind_pf failed\n");
        return -1;
    }

    if (nfq_unbind_pf(h, AF_INET6) < 0) {
        printf("nfq_unbind_pf failed\n");
        return -1;
    }

    if (nfq_bind_pf(h, AF_INET) < 0) {
        printf("nfq_bind_pf failed\n");
        return -1;
    }

    if (nfq_bind_pf(h, AF_INET6) < 0) {
        printf("nfq_bind_pf failed\n");
        return -1;
    }

    /* if comment above bind/unbind, the create fail too */
    struct nfq_q_handle *qh = nfq_create_queue(h, NFQ_NUM, nfq_cb, NULL);
    if (!qh) {
        printf("nfq_create_queue failed\n");
        return -1;
    }

    /* ... */
}

int main() {
    nfq_demo();
    return 0;
}
