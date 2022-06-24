#include "Tree.h"
//  ахмюпмне депебн я опълшл наунднл



//	онксвемхе бшянрш
unsigned int Tree::height(node* p) {
    return p ? p->height : 0;
}



//	аюкюмяхпнбйю
int Tree::bfactor(node* p) {
    
    return height(p->right) - height(p->left);
}



//	аюкюмяхпнбйю бшянрш
void Tree::fixHeight(node* p) {
    
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);

    p->height = (hl > hr ? hl : hr) + 1;
}


//  опюбши онбнпнр бнйпсц п
node* Tree::rotateRight(node* p) {
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixHeight(p);
    fixHeight(q);
    return q;
}



//  кебши онбнпнр бнйпсц Q
node* Tree::rotateLeft(node* q) {
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixHeight(q);
    fixHeight(p);
    return p;
}



//  аюкюмяхпнбйю сгкю п
node* Tree::balance(node* p) {
    fixHeight(p);
    if (bfactor(p) == 2)
    {
        if (bfactor(p->right) < 0)
            p->right = rotateRight(p->right);
        return rotateLeft(p);
    }
    if (bfactor(p) == -2)
    {
        if (bfactor(p->left) > 0)
            p->left = rotateLeft(p->left);
        return rotateRight(p);
    }
    return p; // аюкюмяхпнбйю ме мсфмю
}



//  бярюбйю йкчвю K б депебн я йнпмел P
node* Tree::insert(node* p, clientTree k) {
    
    if (!p) return new node(k);

    if (k.pasport < p->key.pasport)
        p->left = insert(p->left, k);
    else if (k.pasport > p->key.pasport) {
        p->right = insert(p->right, k);
    }
    else {
        cout << "нЬХАЙЮ. рЮЙНИ ЙКХЕМР СФЕ ЯСЫЕЯРБСЕР." << endl;
    }
    return balance(p);
}



//  днаюбхрэ йкхемрю
void Tree::addKlitnt(clientTree k) {
    if (root == NULL) {
        root = new node(k);
    }
    else {
        root = insert(root, k);
    }
}

void Tree::deleteKlient(string pasport) {
    if (root == NULL) {
        root = remove(root, pasport);
    }
    else {
        root = remove(root, pasport);
    }
}



//  онхяйю сгкю я лхмхлюкэмшл йкчвнл б онддепебе P
node* Tree::findMin(node* p) {
    return p->left ? findMin(p->left) : p;
}



//  сдюкемхе сгкю я лхмхлюкэмшл йкчвнл б онддепебе P
node* Tree::removeMin(node* p) {
    
    if (p->left == 0)
        return p->right;
    p->left = removeMin(p->left);
    return balance(p);
}



// сдюкемхе хг депебю йкхемрю он ярпнйе оюяонпрю
node* Tree::remove(node* p, string k) {
    
    if (!p) return 0;
    if (k < p->key.pasport)
        p->left = remove(p->left, k);
    else if (k > p->key.pasport)
        p->right = remove(p->right, k);
    else //  k == p->key 
    {
        node* q = p->left;
        node* r = p->right;
        delete p;
        if (!r) return q;
        node* min = findMin(r);
        min->right = removeMin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}



////  сдюкемхе бяецн депебю
//node* Tree::removeAll(node* p) {
//    while ((p->left != NULL) && (p->right != NULL)) {
//        removeMin(p);
//    }
//    delete p;
//    p = NULL;
//    return p;
//}

//  сдюкемхе бяецн депебю
void Tree::removeAll() {
    while ((root->left != NULL) && (root->right != NULL)) {
        removeMin(root);
    }
    delete root;
    root = NULL;
}



//  онхяй йкхемрю б депебе он ярпнйе оюяонпрю
void Tree::findCustomer(node* p, string a) {
    if (p != NULL) {
        if (p->key.pasport == a) {

                cout << " тхн: " << p->key.FIO << endl
                << " оЮЯОНПР: " << p->key.pasport << endl
                << " лЕЯРН Х ДЮРЮ ПНФДЕМХЪ: " << p->key.placeAndDate << endl
                << " юДПЕЯЯ: " << p->key.address << endl;
        }
        findCustomer(p->left, a);
        findCustomer(p->right, a);
    }
}



//  опнбепйю еярэ кх сфе йкхемр я рюйхл оюяонпрнл
bool Tree::checkPasport(string a, node* p) {
    while (p != NULL) {
        if (a < p->key.pasport)
            p = p->left;
        else if (a > p->key.pasport) {
            p = p->right;
        }
        else {
            if (a == p->key.pasport) {
                return 1;
            }
        }
    }
    return 0;
}

//  бяонлнцюрекэмюъ тсмйжхъ дкъ бшбндю
void Tree::minShow(node* p) {
    if (p != NULL) {
        cout << " тхн: " << setw(30) << p->key.FIO << setw(20) << "оЮЯОНПР: " << setw(20) << p->key.pasport << endl;
    }
    if (p->left != NULL) {
        minShow(p->left);
    }
    if (p->right != NULL) {
        minShow(p->right);
    }
}


//  бшбнд бяеу йкхемрнб
void Tree::showKlient() {
    if (root == NULL) {
        cout << "аЮГЮ ДЮММШУ ОСЯРЮ.\n";
    }
    else {
        minShow(root);
    }
}


//  онхяй йкхемрю он ярпнйе
void Tree::findKlientOnString(node* p, string str, bool &chek) {
    if (p != NULL) {
        if (findString(p->key.address, str) || findString(p->key.FIO, str)) {
            chek = true;
            cout << " тхн: " << setw(30) << p->key.FIO << setw(20) << " оЮЯОНПР: " << setw(20) << p->key.pasport << " юДПЕЯЯ: " << setw(20) << p->key.address << endl;
        }
    }
    if (p->left != NULL) {
        findKlientOnString(p->left, str, chek);
    }
    if (p->right != NULL) {
        findKlientOnString(p->right, str, chek);
    }
}


//  опнбепйю бунфдемхъ ондярпнйх б ярпнйс опълюъ
//bool Tree::findString(string s, string c)
//{
//    int i, j;
//    bool itog = false;
//    for (i = 0; i < s.length() - c.length() + 1; i++)
//    {
//        for (j = 0; j < c.length(); j++) {
//            if (c[j] != s[i + j]) {
//                break;
//            }
//            else if (j == (c.length() - 1)) {
//                itog = true;
//                break;
//            }
//        }
//    }
//    return itog;
//}
bool Tree::findString(string str2, string str1) {
    int i, j;
    int len1 = str1.length();
    int len2 = str2.length();

    for (i = 0; i <= len2 - len1; i++) {
        for (j = 0; j < len1; j++)
            if (str2[i + j] != str1[j]) {
                break;
            }

        if (j == len1) {
            return true;
        }
    }

    return false;
}

