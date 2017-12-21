#include <stdio.h>
#include <stdlib.h>
#include "gcd.h"

enum input_mode {CMDARGS, INFTLOOP};

struct lnode
{
	uint64_t data;
	/*
	 * Initially, a node has no child
	 */
	struct lnode *next;
};

void exit_too_few_arguments()
{
	printf("The number of arguments provided is incorrect; You need to provide"
		" at least 2 or more positive integers or none at all. For the latter case,"
		" the program reads the input.\n");
	exit(EXIT_FAILURE);
}

struct lnode* obtain_list_argv(int argc, char const *argv[])
{
	struct lnode *head = malloc(sizeof(struct lnode));
	struct lnode *node = head;
	int index = 1;
	while (index < argc) {
		node->data = strtoull(argv[index], NULL, 0);
		node->next = malloc(sizeof(struct lnode));
		node = node->next;
		index++;
	}
	// The last node is a dummy node
	node->data = 0;
	node->next = NULL;
	return head;
}

struct lnode* obtain_list_input()
{
	struct lnode *head = malloc(sizeof(struct lnode));
	struct lnode *node = head;
	int index = 1;
	uint64_t value;
	int ret_val = scanf("%llu", &value);
	while (ret_val == 1 && value != 0) {
		node->data = value;
		node->next = malloc(sizeof(struct lnode));
		node = node->next;
		index++;
		ret_val = scanf("%llu", &value);
	}
	// The last node is a dummy node
	node->data = 0;
	node->next = NULL;
	return head;
}

struct lnode* obtain_list(unsigned char input_mode, int argc, char const *argv[])
{
	switch (input_mode) {
		case CMDARGS:
			return obtain_list_argv(argc, argv);
		case INFTLOOP:
			return obtain_list_input();
	}
}

unsigned char decide_input_mode(int argc, char const *argv[])
{
	switch (argc) {
		case 1:
			// The program has been invoked from its name only with
			// No command-line arguments. Read the integers from input
			return INFTLOOP;
		case 2:
			// The user has provided the program name and only one number.
			// This program needs at leat 2 to work (and make sense).
			exit_too_few_arguments();
		default:
			// 2 or more numbers so obtain input from command-line arguments.
			return CMDARGS;
	}
}

int main(int argc, char const *argv[])
{
	unsigned char input_mode = decide_input_mode(argc, argv);
	struct lnode *node = obtain_list(input_mode, argc, argv);
	uint64_t divisor = 0;
	while (node != NULL) {
		divisor = gcd(node->data, divisor);
		node = node->next;
	}
	printf("%"PRIu64"\n", divisor);
	return EXIT_SUCCESS;
}