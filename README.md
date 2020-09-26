# Toll_System

Toll plaza system coding using the concept of semaphore and mutex[Code](toll_plaza.c)

Make file run-
run:toll_plaza.c
	gcc toll_plaza.c -o toll_plaza -lpthread -o all

4 toll palza system can have one car at a time. The car will be queued at a particular number. Each car(having particular ID) will be checked at the toll according to their queue status.
