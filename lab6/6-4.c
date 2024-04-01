#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {
        p = (struct tnode *)malloc(sizeof(struct tnode));
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
    } else if (cond < 0) {
        p->left = addtree(p->left, w);
    } else {
        p->right = addtree(p->right, w);
    }
    return p;
}

void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%s: %d\n", p->word, p->count);
        treeprint(p->right);
    }
}

void freetree(struct tnode *p) {
	if (p != NULL) {
		freetree(p->left);
		freetree(p->right);
		free(p->word);
		free(p);
	}
}

int main() {
    struct tnode *root;
    char sentence[] = {"now is the time for all good men to come to the aid of their party"};
    char *word;

    root = NULL;
    word = strtok(sentence, " ");
    while (word != NULL) {
	    root = addtree(root, word);
	    word = strtok(NULL, " ");
    }
    treeprint(root);
    freetree(root);

    return 0;
}

