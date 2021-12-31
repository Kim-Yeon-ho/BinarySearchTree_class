#include <iostream>
#include <string>
using namespace std;
string error = "out-of-key";

class BinaryNode { //��� Ŭ����
	friend class BinarySearchTree;
private:
	string key;
	int value;
	BinaryNode* left;
	BinaryNode* right;

public:
	BinaryNode(string key = " ", int value = 0, BinaryNode* left = nullptr, BinaryNode* right = nullptr) {
		this->key = key;
		this->value = value;
		this->left = left;
		this->right = right;
	}
	void setKey(string key) { this->key = key; }
	string getKey() { return this->key; }
	void setValue(int value) { this->value = value; }
	int getValue() { return this->value; }
	void setLeft(BinaryNode* left) { this->left = left; }
	BinaryNode* getLeft() { return this->left = left; }
	void setRight(BinaryNode* right) { this->right = right; }
	BinaryNode* getRight() { return this->right = right; }

	bool isLeaf() {
		return this->left == nullptr && this->right == nullptr;
	}

	bool hasTwoChildren() {
		return this->left != nullptr && this->right != nullptr;
	}

	bool hasOneChildren() {
		bool hasOnlyLeft = this->left != nullptr && this->right == nullptr;
		bool hasOnlyRight = this->left == nullptr && this->right != nullptr;

		return hasOnlyLeft || hasOnlyRight;
	}
};

class BinaryTree { //����Ʈ��
protected:
	BinaryNode* root;
public:
	BinaryTree() { this->root = nullptr; }
	~BinaryTree() {
		removeNodes(this->root);
	}

	void removeNodes(BinaryNode* node) {
		if (node != nullptr) {
			removeNodes(node->getLeft());
			removeNodes(node->getRight());
			delete node;
		}
	}

	bool empty() { return this->root == nullptr; }
	int size() {
		return(this->empty()) ? 0 : size(this->root);
	}

	int size(BinaryNode* node) { //����� ���� ����
								// �� ���� Ʈ���� ����� ���� �ڱ��ڽ��� ���ϰ� ��ȯ�Ѵ�.
		if (node == nullptr) return 0;
		int cnt = size(node->getLeft());
		cnt += 1;
		cnt += size(node->getRight());
		return cnt;
	}
};

class BinarySearchTree : public BinaryTree { //���� Ž�� Ʈ��
public:
	int search(string key) {
		BinaryNode* node = search(this->root, key);
		if (node == nullptr) throw error;
		return node->value;
	}
	void insert(string key, int value) {
		if (empty()) this->root = new BinaryNode(key, value);
		else insert(this->root, key, value);
	}
	void remove(string key) {
		BinaryNode* node = remove(this->root, nullptr, key);
		if (node == nullptr) {
			throw error;
		}
		delete node;
	}

private:
	BinaryNode* search(BinaryNode* node, string key) {
		if (node == nullptr || key == node->key) return node;
		else if (key < node->key) return search(node->left, key);
		else return search(node->right, key);
	}

	void insert(BinaryNode* node, string key, int value) {
		if (key == node->key) node->value = value;
		else if (key < node->key) {
			if (node->left == nullptr) {
				node->left = new BinaryNode(key, value);
			}
			else insert(node->left, key, value);
		}
		else {
			if (node->right == nullptr) {
				node->right = new BinaryNode(key, value);
			}
			else insert(node->right, key, value);
		}
	}

	BinaryNode* remove(BinaryNode* node, BinaryNode* parent, string key) {
		if (node == nullptr) {
			return nullptr;
		}
		if (key < node->key) {
			return remove(node->left, node, key);
		}

		else if (key > node->key) {
			return remove(node->right, node, key);
		}
		else {
			if (node->hasTwoChildren()) {
				BinaryNode* succ = leftmost(node->right);
				node->key = succ->key;
				node->value = succ->value;
				succ = this->remove(node->right, node, succ->key);
				return succ;
			}
			else if (node->hasOneChildren()) {
				BinaryNode* child = (node->left != nullptr) ? node->left : node->right;
				if (node == this->root) {
					this->root = child;
				}
				else {
					if (parent->left == node) parent->left = child;
					else parent->right = child;
				}
				return node;
			}
			else if (node->isLeaf()) {
				if (node == this->root) {
					this->root = nullptr;
				}
				else {
					if (parent->left == node) parent->left = nullptr;
					else parent->right = nullptr;
				}
				return node;
			}
		}
	}


	BinaryNode* leftmost(BinaryNode* node) {//
		while (node->left != nullptr) {
			node = node->left;
		}
		return node;
	}
};

int main() {
	BinarySearchTree Bst;
	int loop = 0;
	string Com = "";//��ɾ� ����;
	string key; int value;

	cin >> loop;

	for (int i = 0; i < loop; i++) {
		cin >> Com;
		if (Com == "empty") { //empty �޼ҵ�
			if (Bst.empty() == true) { cout << "empty\n"; }
			else cout << "not empty\n";
		}
		else if (Com == "insert") { //insert �޼ҵ�
			cin >> key >> value;
			Bst.insert(key, value);
		}
		else if (Com == "search") { // search �޼ҵ�
			cin >> key;
			try {
				cout << Bst.search(key) << "\n";
			}
			catch (string exception) {
				cout << exception << "\n";
			}
		}
		else if (Com == "remove") { //remove �޼ҵ�
			cin >> key;
			try {
				Bst.remove(key);
			}
			catch (string exception) {
				cout << exception << "\n";
			}
		}
		else if (Com == "size") { //size �޼ҵ�
			cout << Bst.size() << "\n";
		}
	}

	return 0;
}