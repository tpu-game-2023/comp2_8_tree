#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include <stdlib.h>

#include "../include/lib_func.h"


// 2分木の初期化
void initialize(tree* t)
{
	if (t == NULL) return;

	t->root = NULL;
}

static void release_recursive(node* n)
{
	if (n == NULL) return;

	if (n->right) {
		release_recursive(n->right);
		n->right = NULL;
	}

	if (n->left) {
		release_recursive(n->left);
		n->left = NULL;
	}

	free(n);
}

// 使用メモリの全解放
void finalize(tree* t)
{
	if (t == NULL) return;

	release_recursive(t->root);
	t->root = NULL;
}


static node* generate(int key, const char* value)
{
	node* p = (node*)malloc(sizeof(node));

	if (p == NULL) return NULL;

	p->key = key;
	int n = (int)strlen(value);
	memcpy(p->value, value, strlen(value)+1);

	p->left = p->right = NULL;

	return p;
}

// keyの値を見てノードを追加する
bool add(tree* t, int key, const char* value)
{
	if (t == NULL) return false;

	node* p = generate(key, value);
	if (p == NULL) return false;// メモリ確保できなかった。

	if (t->root == NULL) {
		t->root = p;
		return true;
	}
	node* n = t->root;
	while (1)
	{
		if (n->key == p->key)
		{
			memcpy(n->value, p->value, strlen(p->value) + 1);
			free(p);
			break;
		}
		if (n->key > p->key)
		{
			if (!n->left)
			{
				n->left = p;
				break;
			}
			n = n->left;

		}
		else
		{
			if (!n->right)
			{
				n->right = p;
				break;
			}
			n = n->right;
		}
		
	}
	// Todo: t->rootの下にkeyの値の大小でleftかrightを切り替えながらpを追加する処理を実装する
	return true;
}

// keyの値を見てノードを検索して、値を取得する
const char* find(const tree* t, int key)
{
	if (t == NULL) return NULL;
	node* n = t->root;
	while (1)
	{
		if (!n)
		{
			return NULL;
		}
		if (n->key == key)
		{
			return n->value;
		}

		if (n->key > key)
		{
			n = n->left;
		}
		else
		{
			n = n->right;
		}
	}
	// ToDo: 実装する
}
void callFunc(const node* p, void (*func)(const node* p))
{
	if (p == NULL) return;
	callFunc(p->left, func);
	func(p);
	callFunc(p->right, func);
}
// keyの小さな順にコールバック関数funcを呼び出す
void search(const tree* t, void (*func)(const node* p))
{
	if (t == NULL) return;
	callFunc(t->root, func);

	// ToDo: 実装する
}