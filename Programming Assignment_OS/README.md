# PRODUCER CONSUMER PROBLEM IN C WITH SEMAPHORES
The code includes *producer.c* and *consumer.c* files which are run simultaneosuly to simulate the problem as follows
$ gccproducer.c -pthread -lrt -o producer
$ gccconsumer.c -pthread -lrt -o consumer
$ ./producer & ./consumer &