#include "declaration.h"
RBtree tree;

void addNum()
{
	int n;
	int num;
	puts("	plz enter the number of node you want to insert to the rbtree.\n");
	printf("Enter: ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		printf("Enter node: ");
		scanf("%d", &num);
		insert(&tree, num);
	}
	puts("	INSERT SUCCEED.\n");
}
void deleteNum()
{
	int n;
	int num;
	puts("	plz enter the number of node you want to erase from the rbtree.\n");
	printf("Enter: ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		printf("Enter node: ");
		scanf("%d", &num);
		erase(&tree, num);
	}
	puts("	DELETE SUCCEED.\n");
}
void findNum()
{
	int num;
	printf("	plz enter the node of node you want to find.\n");
	printf("Enter:");
	scanf("%d", &num);
	int ans = find(&tree, (&tree)->root, num);
	if (ans == -1)
		printf("%d can not be found in the tree\n", num);
	else
		printf("The node is at the %d position\n", ans);
}
int main()
{
	initializeTree(&tree, 2);
	for (int i = 0; i < 9; i++)
	{
		insert(&tree, rand() % 100);
	}

	int input;
	while (1)
	{
		puts("======= MENU =======");
		puts("0.EXIT.");
		puts("1.INSERT SOME NODE.");
		puts("2.ERASE SOME NODE.");
		puts("3.ASCENDING ORDER");
		puts("4.DECENDING ORDER");
		puts("5.FIND A NODE");
		puts("6.PREORDER");
		puts("7.INORDER");
		puts("8.POSTORDER");
		puts("9.DRAW TREE");
		puts("====================");
		printf("Enter: ");
		scanf("%d", &input);
		if (input == 0)break;
		switch (input)
		{
		case 0:
			break;
		case 1:
			addNum();
			break;
		case 2:
			deleteNum();
			break;
		case 3:
			inOrder(&tree, (&tree)->root);
			printf("\n");
			break;
		case 4:
			reverseOrder(&tree, (&tree)->root);
			printf("\n");
			break;
		case 5:
			findNum();
			break;
		case 6:
			preOrder(&tree, (&tree)->root);
			printf("\n");

			break;
		case 7:
			inOrder(&tree, (&tree)->root);
			printf("\n");
			break;
		case 8:
			postOrder(&tree, (&tree)->root);
			printf("\n");
			break;
		case 9:
			printTree(tree.root);
			break;
		default:
			puts("There is no option of this number,plz try again.");
			break;
		}
	}

	return 0;
}