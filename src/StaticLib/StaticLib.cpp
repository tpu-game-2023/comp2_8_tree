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
static bool insert(node* origin, node* p)
{
	if (p->key < origin->key)
	{
		if (origin->left == NULL)
		{
			origin->left = p;
			return(origin->left != NULL);
		}
		return insert(origin->left, p);
	}
	else if (origin->key < p->key)
	{
		if (origin->right == NULL)
		{
			origin->right = p;
			return (origin->right != NULL);
		}
		return insert(origin->right, p);
	}

	strcpy_s(origin->value, 256, p->value);
	free(p);
	return true;
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

	// Todo: t->rootの下にkeyの値の大小でleftかrightを切り替えながらpを追加する処理を実装する
	return insert(t->root, p);
}
static const char* finder(const node* p, int key)
{
	if (p == NULL)return NULL;

	if (p->key == key)return p->value;

	return finder((key < p->key) ? p->left : p->right, key);
}
// keyの値を見てノードを検索して、値を取得する
const char* find(const tree* t, int key)
{
	if (t == NULL)
		return NULL;
	// ToDo: 実装する
	node* q = t->root;
	return finder(t->root, key);
}
void searcher(const node* n, void (*func)(const node* p))
{
	if (n == NULL)return;
	searcher(n->left, func);
	func(n);
	searcher(n->right, func);
	
}

// keyの小さな順にコールバック関数funcを呼び出す
void search(const tree* t, void (*func)(const node* p))
{
	// ToDo: 実装する
	if (t == NULL) return;
	searcher(t->root, func);
}