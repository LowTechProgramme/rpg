#include <iostream>
using namespace std;

//���������
class Item {
public:
    //���캯������ʼ�����ߵ����ơ��۸�Ч��
    Item(string name, int price, int effect) {
        this->name = name;
        this->price = price;
        this->effect = effect;
    }
    //��ȡ���ߵ�����
    string getName() {
        return name;
    }
    //��ȡ���ߵļ۸�
    int getPrice() {
        return price;
    }
    //��ȡ���ߵ�Ч��
    int getEffect() {
        return effect;
    }
private:
    string name; //��������
    int price; //���߼۸�
    int effect; //����Ч��
};

//���������
class Player {
public:
    //���캯������ʼ����ҵ���������������������Ǯ������
    Player(double life, int attack, int defense, int money) {
        this->life = life;
        this->attack = attack;
        this->defense = defense;
        this->money = money;
        for (int i = 0; i < 10; i++) {
            bag[i] = NULL; //����Ϊ��
        }
    }
    //��ȡ��ҵ�����
    double getLife() {
        return life;
    }
    //��ȡ��ҵĹ���
    int getAttack() {
        return attack;
    }
    //��ȡ��ҵķ���
    int getDefense() {
        return defense;
    }
    //��ȡ��ҵĽ�Ǯ
    int getMoney() {
        return money;
    }
    //������ҵ�����
    void setLife(double life) {
        this->life = life;
    }
    //������ҵĹ���
    void setAttack(int attack) {
        this->attack = attack;
    }
    //������ҵķ���
    void setDefense(int defense) {
        this->defense = defense;
    }
    //������ҵĽ�Ǯ
    void setMoney(int money) {
        this->money = money;
    }
    //��ȡ��ҵı���
    Item** getBag() {
        return bag;
    }
    //������ߣ�����Ϊ���߶��������
    void buyItem(Item* item, int number) {
        if (item == NULL || number <= 0) { //������Ч
            cout << "��Ч�Ĺ�������" << endl;
            return;
        }
        int total_price = item->getPrice() * number; //�����ܼ�
        if (money < total_price) { //��Ǯ����
            cout << "��û���㹻�Ľ�Ǯ����" << item->getName() << "��" << endl;
            return;
        }
        money -= total_price; //�۳���Ǯ
        cout << "�㻨��" << total_price << "Ԫ������" << number << "��" << item->getName() << "��" << endl;
        for (int i = 0; i < 10; i++) { //����������Ѱ�ҿ�λ��ŵ���
            if (bag[i] == NULL) {
                bag[i] = item; //��ŵ���
                break;
            }
        }
    }

    //ʹ�õ��ߣ�����Ϊ���߶���͹������ָ�루����У�
    void useItem(Item* item, int* monster_attack, int* monster_defense) {
        if (item == NULL) { //������Ч
            cout << "��Ч��ʹ������" << endl;
            return;
        }
        cout << "��ʹ����" << item->getName() << "��" << endl;
        switch (item->getEffect()) { //���ݵ���Ч��ִ�в�ͬ����
        case 1: //��������ֵ
            life += 50;
            cout << "�������ֵ������50�㣡" << endl;
            break;
        case 2: //���ӹ�����
            attack += 10;
            cout << "��Ĺ�����������10�㣡" << endl;
            break;
        case 3: //���ӷ�����
            defense += 10;
            cout << "��ķ�����������10�㣡" << endl;
            break;
        case 4: //���ٹ��﹥����
            if (monster_attack == NULL) { //������Ч
                cout << "û�й������ʹ��������ߣ�" << endl;
                return;
            }
            *monster_attack -= 10;
            cout << "����Ĺ�����������10�㣡" << endl;
            break;
        case 5: //���ٹ��������
            if (monster_defense == NULL) { //������Ч
                cout << "û�й������ʹ��������ߣ�" << endl;
                return;
            }
            *monster_defense -= 10;
            cout << "����ķ�����������10�㣡" << endl;
            break;
        default: //��Ч��Ч��
            cout << "�������û���κ�Ч����" << endl;
        }
        for (int i = 0; i < 10; i++) { //����������Ѱ�ҵ���λ��
            if (bag[i] == item) {
                bag[i] = NULL; //�Ƴ�����
                break;
            }
        }
    }

    //��ʾ��ҵ�״̬
    void showStatus() {
        cout << "�������ֵ��" << life << endl;
        cout << "��Ĺ�������" << attack << endl;
        cout << "��ķ�������" << defense << endl;
        cout << "��Ľ�Ǯ��" << money << endl;
    }

    //��ʾ��ҵı���
    void showBag() {
        cout << "��ı�����" << endl;
        for (int i = 0; i < 10; i++) {
            if (bag[i] != NULL) { //����е��ߣ���ʾ�����ƺͼ۸�
                cout << i + 1 << ". " << bag[i]->getName()
                    << "���۸�" << bag[i]->getPrice()
                    << "��" << endl;
            }
            else { //���û�е��ߣ���ʾ��λ
                cout << i + 1 << ". ��" << endl;
            }
        }
    }

private:
    double life; //����ֵ
    int attack; //������
    int defense; //������
    int money; //��Ǯ
    Item* bag[10]; //�����������10������
};

//�����̵���
class Shop {
public:
    //���캯������ʼ���̵�����ƺ���Ʒ�б�
    Shop(string name, Item* items[], int size) {
        this->name = name;
        this->items = items;
        this->size = size;
    }
    //��ȡ�̵������
    string getName() {
        return name;
    }
    //��ȡ�̵����Ʒ�б�
    Item** getItems() {
        return items;
    }
    //��ȡ�̵����Ʒ����
    int getSize() {
        return size;
    }
private:
    string name; //�̵�����
    Item** items; //��Ʒ�б�ָ����߶����ָ������
    int size; //��Ʒ����
};

//������̵�ϵͳ�İ�ť��
class ShopButton {
public:
    //���캯������ʼ����ť�����ƺ͹������̵����ָ��
    ShopButton(string name, Shop* shop) {
        this->name = name;
        this->shop = shop;
    }
    //��ȡ��ť������
    string getName() {
        return name;
    }
    //��ȡ��ť�������̵����ָ��
    Shop* getShop() {
        return shop;
    }
private:
    string name; //��ť����
    Shop* shop; //�������̵����ָ��
};

//������̵�ϵͳ�ĺ���������Ϊ��Һ͹������ָ�루����У�
void openShopSystem(Player* player, int* monster_attack, int* monster_defense) {
    if (player == NULL) { //������Ч
        cout << "��Ч����Ҷ���" << endl;
        return;
    }
    //�����̵����͵��߶���    
    Item* item1 = new Item("����ҩˮ", 10, 1); //Ч��Ϊ��������ֵ
    Item* item2 = new Item("����ҩˮ", 20, 2); //Ч��Ϊ���ӹ�����
    Item* item3 = new Item("����ҩˮ", 20, 3); //Ч��Ϊ���ӷ�����
    Item* item4 = new Item("�Ƽ׵�", 30, 4); //Ч��Ϊ���ٹ��﹥����
    Item* item5 = new Item("�ƶܵ�", 30, 5); //Ч��Ϊ���ٹ��������
    Item* items[5] = { item1, item2, item3, item4, item5 }; //��Ʒ�б�
    Shop* shop = new Shop("��Ӧ�̵�", items, 5); //�̵����

    //�����̵갴ť����
    ShopButton* button = new ShopButton("���̵�", shop);

    //��ʾ��ť����
    cout << "�㿴����һ����ť������д�ţ�" << button->getName() << endl;

    //ѯ���Ƿ��°�ť
    cout << "���Ƿ�Ҫ���������ť����y/n��" << endl;
    char choice;
    cin >> choice;

    if (choice == 'y' || choice == 'Y') { //���ѡ���°�ť
        cout << "�㰴���������ť��" << button->getShop()->getName() << "���ˣ�" << endl;
        bool exit = false; //�Ƿ��˳��̵�ı�־
        while (!exit) { //ѭ��ֱ���˳��̵�
            //��ʾ��ҵ�״̬�ͱ���
            player->showStatus();
            player->showBag();

            //��ʾ�̵����Ʒ�б�
            cout << button->getShop()->getName() << "����Ʒ�б�" << endl;
            for (int i = 0; i < button->getShop()->getSize(); i++) {
                cout << i + 1 << ". " << button->getShop()->getItems()[i]->getName()
                    << "���۸�" << button->getShop()->getItems()[i]->getPrice()
                    << "��" << endl;
            }
            cout << "0. �˳��̵�" << endl;

            //ѯ���Ƿ����ʹ����Ʒ
            cout << "���Ƿ�Ҫ�����ʹ����Ʒ����b/u/n��" << endl;
            cin >> choice;

            if (choice == 'b' || choice == 'B') { //���ѡ������Ʒ
                int index; //��Ʒ���
                int number; //��Ʒ����
                cout << "��������Ҫ�������Ʒ��ţ�1-5����" << endl;
                cin >> index;
                if (index < 1 || index > 5) { //�����Ч
                    cout << "��Ч����Ʒ��ţ�" << endl;
                    continue;
                }
                cout << "��������Ҫ�������Ʒ������" << endl;
                cin >> number;
                if (number <= 0) { //������Ч
                    cout << "��Ч����Ʒ������" << endl;
                    continue;
                }
                player->buyItem(button->getShop()->getItems()[index - 1], number); //��ҹ�����Ʒ
            }
            else if (choice == 'u' || choice == 'U') { //���ѡ��ʹ����Ʒ
                int index; //��Ʒ���
                cout << "��������Ҫʹ�õ���Ʒ��ţ�1-10����" << endl;
                cin >> index;
                if (index < 1 || index > 10) { //�����Ч
                    cout << "��Ч����Ʒ��ţ�" << endl;
                    continue;
                }
                player->useItem(player->getBag()[index - 1], monster_attack, monster_defense); //���ʹ����Ʒ
            }
            else if (choice == 'n' || choice == 'N') { //���ѡ�񲻹����ʹ����Ʒ
                exit = true; //�˳��̵�
                cout << "���뿪��" << button->getShop()->getName() << "��"
                    << endl;
            }
            else { //��Ч������
                cout << "��Ч�����룡"
                    << endl;
            }
        }
    }
    else if (choice == 'n' || choice == 'N') { //���ѡ�񲻰��°�ť
        cout << "��û�а��������ť��" << button->getShop()->getName() << "û�д򿪣�" << endl;
    }
    else { //��Ч������
        cout << "��Ч�����룡" << endl;
    }
}

//�����������Դ���
int main() {
    //������Ҷ���
    Player* player = new Player(100, 20, 10, 100);

    //�����������ָ�룬����ģ�����Ĺ������ͷ�����
    int monster_attack = 30;
    int monster_defense = 20;

    //���̵�ϵͳ
    openShopSystem(player, &monster_attack, &monster_defense);

    return 0;
}
