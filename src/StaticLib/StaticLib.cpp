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

	if (t->root == NULL) {// 一番上のノードが空の時
		t->root = p;
		return true;
	}

	// Todo: t->rootの下にkeyの値の大小でleftかrightを切り替えながらpを追加する処理を実装する
	node* n = t->root;

	while (1)
	{
		if (n->key == key) {// 追加するノードのキーが今調べているノードのキーと一致してる場合->valueを追加するノードのvalueに書き換える
			memcpy(n->value, value, strlen(value) + 1);
			release_recursive(p);
			break;
		}
		else if (key < n->key) {// 追加するノードのキーが今調べているノードのキーより小さい時->左に
			if (n->left == NULL) {// 左のノードが空であればそこに追加
				n->left = p;
				break;
			}

			n = n->left;// 調べるキーを左のキーに移す
		}
		else {// 追加するノードのキーが今調べているノードのキーより大きい時->右に
			if (n->right == NULL) {// 右のノードが空であればそこに追加
				n->right = p;
				break;
			}

			n = n->right;// 調べるキーを右のキーに移す
		}
	};

	return true;
}

// keyの値を見てノードを検索して、値を取得する
const char* find(const tree* t, int key)
{
	// ToDo: 実装する
	if (t == NULL) return NULL;

	const node* n = t->root;
	while (n != NULL) {// nが空のノードになったらやめる
		if (n->key == key) return n->value;// keyが合えばそのnのvalueを返す

		else if (key < n->key)// 検索しているノードのキーが今調べているキーより小さい時->左に
		{
			n = n->left;
		}
		else// 検索しているノードのキーが今調べているキーより大きい時->右に
		{
			n = n->right;
		}
	}
	return NULL;
}

void search_sub(const node* p, void (*func)(const node* p))
{
	if (p == NULL) return;

	if (p->left) search_sub(p->left, func);
	func(p);
	if (p->right) search_sub(p->right, func);
}

// keyの小さな順にコールバック関数funcを呼び出す
void search(const tree* t, void (*func)(const node* p))
{
	// ToDo: 実装する
	if (t == NULL) return;

	search_sub(t->root, func);
}