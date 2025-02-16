#include <iostream>
#include <string>
using namespace std;

// Estrutura para armazenar os dados do paciente
struct Patient
{
    int id;
    int priority;
    string name;
    string phone;
    string history;
};

// Nó da árvore AVL
struct AVLNode
{
    Patient patient;
    AVLNode *left;
    AVLNode *right;
    int height;
};

// Estrutura de nó para a pilha
struct StackNode
{
    AVLNode *treeNode;
    StackNode *next;
};

// Estrutura da pilha
struct Stack
{
    StackNode *top;
};

// Função para buscar paciente por ID
AVLNode *searchById(AVLNode *node, int id)
{
    if (node == nullptr || node->patient.id == id)
        return node;

    if (id < node->patient.id)
        return searchById(node->left, id);
    else
        return searchById(node->right, id);
}

// Função para buscar pacientes por prioridade e nome
void searchByPriority(AVLNode *node, int priority)
{
    if (node == nullptr)
        return;

    cout << "Paciente(s) encontrado(s):\n";
    searchByPriority(node->left, priority);

    if (node->patient.priority == priority)
    {
        cout << "ID: " << node->patient.id << "\t| ";
        cout << "Nome: " << node->patient.name << "\t| ";
        cout << "Prioridade: " << node->patient.priority << "\t| ";
        cout << "Telefone: " << node->patient.phone << "\t| ";
        cout << "Historico: " << node->patient.history << "\n";
    }

    searchByPriority(node->right, priority);
}

// Função para buscar pacientes por nome
void searchByName(AVLNode *node, string name)
{
    if (node == nullptr)
        return;

    cout << "Paciente(s) encontrado(s):\n";
    searchByName(node->left, name);

    if (node->patient.name == name)
    {
        cout << "ID: " << node->patient.id << "\t| ";
        cout << "Nome: " << node->patient.name << "\t| ";
        cout << "Prioridade: " << node->patient.priority << "\t| ";
        cout << "Telefone: " << node->patient.phone << "\t| ";
        cout << "Historico: " << node->patient.history << "\n";
    }

    searchByName(node->right, name);
}

// Função que retorna a altura do nó
int height(AVLNode *node)
{
    return node ? node->height : 0;
}

// Retorna o maior entre dois inteiros
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Cria um novo nó com os dados do paciente
AVLNode *createNode(Patient p)
{
    AVLNode *node = new AVLNode;
    node->patient = p;
    node->left = node->right = nullptr;
    node->height = 1;
    return node;
}

// Rotação à direita
AVLNode *rightRotate(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Rotação à esquerda
AVLNode *leftRotate(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;
    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Calcula o fator de balanceamento do nó
int getBalance(AVLNode *node)
{
    return node ? height(node->left) - height(node->right) : 0;
}

// Insere um novo paciente na árvore AVL
AVLNode *insertNode(AVLNode *node, Patient p)
{
    if (node == nullptr)
        return createNode(p);

    // Em caso de prioridades iguais, usa o ID para definir a posição
    if (p.priority < node->patient.priority)
        node->left = insertNode(node->left, p);
    else if (p.priority > node->patient.priority)
        node->right = insertNode(node->right, p);
    else
    {
        if (p.id < node->patient.id)
            node->left = insertNode(node->left, p);
        else
            node->right = insertNode(node->right, p);
    }

    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = getBalance(node);

    // Casos de rotação
    // Left Left
    if (balance > 1 && p.priority < node->left->patient.priority)
        return rightRotate(node);

    // Right Right
    if (balance < -1 && p.priority > node->right->patient.priority)
        return leftRotate(node);

    // Left Right
    if (balance > 1 && p.priority > node->left->patient.priority)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left
    if (balance < -1 && p.priority < node->right->patient.priority)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Inicializa a pilha
void initStack(Stack &s)
{
    s.top = nullptr;
}

// Insere um nó na pilha
void push(Stack &s, AVLNode *node)
{
    StackNode *newNode = new StackNode;
    newNode->treeNode = node;
    newNode->next = s.top;
    s.top = newNode;
}

// Remove e retorna o nó do topo da pilha
AVLNode *pop(Stack &s)
{
    if (s.top == nullptr)
        return nullptr;
    StackNode *temp = s.top;
    AVLNode *node = temp->treeNode;
    s.top = s.top->next;
    delete temp;
    return node;
}

// Verifica se a pilha está vazia
bool isEmpty(Stack &s)
{
    return (s.top == nullptr);
}

// Listar pacientes em ordem de prioridade
void printPatients(AVLNode *root)
{
    Stack s;
    initStack(s);
    AVLNode *current = root;

    while (current != nullptr || !isEmpty(s))
    {
        while (current != nullptr)
        {
            push(s, current);
            current = current->left;
        }

        current = pop(s);
        cout << "ID: " << current->patient.id
             << "\t | Prioridade: " << current->patient.priority
             << "\t | Nome: " << current->patient.name << endl;
        current = current->right;
    }
}

// Encontra o nó com menor valor (mais à esquerda)
AVLNode *minValueNode(AVLNode *node)
{
    AVLNode *current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Remove um nó da árvore AVL
AVLNode *deleteNode(AVLNode *root, int id)
{
    if (root == nullptr)
        return root;

    // Busca pelo nó a ser removido
    if (id < root->patient.id)
        root->left = deleteNode(root->left, id);
    else if (id > root->patient.id)
        root->right = deleteNode(root->right, id);
    else
    {
        // Nó com um ou nenhum filho
        if ((root->left == nullptr) || (root->right == nullptr))
        {
            AVLNode *temp = root->left ? root->left : root->right;

            // Caso sem filhos
            if (temp == nullptr)
            {
                temp = root;
                root = nullptr;
            }
            else               // Caso com um filho
                *root = *temp; // Copia o conteúdo do filho

            delete temp;
        }
        else
        {
            // Nó com dois filhos: obtém o sucessor in-order (menor na subárvore direita)
            AVLNode *temp = minValueNode(root->right);

            // Copia os dados do sucessor
            root->patient = temp->patient;

            // Remove o sucessor
            root->right = deleteNode(root->right, temp->patient.id);
        }
    }

    // Se a árvore tinha apenas um nó, retorna
    if (root == nullptr)
        return root;

    // Atualiza a altura do nó atual
    root->height = 1 + max(height(root->left), height(root->right));

    // Obtém o fator de balanceamento
    int balance = getBalance(root);

    // Casos de rotação

    // Left Left
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void editPatient(AVLNode *root, int id)
{
    AVLNode *found = searchById(root, id);
    if (found != nullptr)
    {
        cout << "Nova prioridade: ";
        cin >> found->patient.priority;
        cout << "Prioridade de paciente atualizada com sucesso.\n";
    }
    else
    {
        cout << "Paciente nao encontrado.\n";
    }
}

int main()
{
    AVLNode *root = nullptr;
    int opcao;
    Patient p;
    int searchId;
    int searchPriority;
    string searchName;

    do
    {
        cout << "\nMenu:\n";
        cout << "1. Inserir paciente\n";
        cout << "2. Listar pacientes (ordem de prioridade)\n";
        cout << "3. Buscar paciente por ID\n";
        cout << "4. Buscar paciente por prioridade\n";
        cout << "5. Buscar paciente por nome\n";
        cout << "6. Editar paciente por ID\n";
        cout << "7. Remover paciente por ID\n";
        cout << "0. Sair\n";

        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if (opcao == 1)
        {
            cout << "Digite o ID do paciente: ";
            cin >> p.id;
            cout << "Digite a prioridade: ";
            cin >> p.priority;
            cin.ignore(); // Limpar o buffer
            cout << "Digite o nome: ";
            getline(cin, p.name);
            cout << "Digite o telefone: ";
            cin >> p.phone;
            cout << "Digite o historico: ";
            cin.ignore();
            getline(cin, p.history);
            root = insertNode(root, p);
        }
        else if (opcao == 2)
        {
            cout << "\nLista de pacientes (ordem de prioridade):\n";
            printPatients(root);
        }
        else if (opcao == 3)
        {
            cout << "Digite o ID do paciente: ";
            cin >> searchId;
            AVLNode *found = searchById(root, searchId);
            if (found != nullptr)
            {
                cout << "\nPaciente encontrado:\n";
                cout << "ID: " << found->patient.id << "\t| ";
                cout << "Nome: " << found->patient.name << "\t| ";
                cout << "Prioridade: " << found->patient.priority << "\t| ";
                cout << "Telefone: " << found->patient.phone << "\t| ";
                cout << "Historico: " << found->patient.history << "\n\n";
            }
            else
            {
                cout << "Paciente nao encontrado.\n";
            }
        }
        else if (opcao == 4)
        {
            cout << "Digite a prioridade: ";
            cin >> searchPriority;
            cout << "\nResultados da busca:\n";
            searchByPriority(root, searchPriority);
        }
        else if (opcao == 5)
        {
            cout << "Digite o nome: ";
            cin.ignore();
            getline(cin, searchName);
            cout << "\nResultados da busca:\n";
            searchByName(root, searchName);
        }
        else if (opcao == 6)
        {
            cout << "Digite o ID do paciente a ser editado: ";
            cin >> searchId;
            editPatient(root, searchId);
        }
        else if (opcao == 7)
        {
            cout << "Digite o ID do paciente a ser removido: ";
            cin >> searchId;

            // Verifica se o paciente existe antes de tentar remover
            if (searchById(root, searchId) == nullptr)
            {
                cout << "Erro: Paciente com ID " << searchId << " nao encontrado.\n";
            }
            else
            {
                root = deleteNode(root, searchId);

                if (root == nullptr)
                {
                    cout << "O ultimo paciente da arvore foi removido.\n";
                }
                else
                {
                    cout << "Paciente removido com sucesso.\n";
                }
            }
        }
        else if (opcao != 0)
        {
            cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);

    return 0;
}