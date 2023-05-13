#include <iostream>
using namespace std;

//定义道具类
class Item {
public:
    //构造函数，初始化道具的名称、价格、效果
    Item(string name, int price, int effect) {
        this->name = name;
        this->price = price;
        this->effect = effect;
    }
    //获取道具的名称
    string getName() {
        return name;
    }
    //获取道具的价格
    int getPrice() {
        return price;
    }
    //获取道具的效果
    int getEffect() {
        return effect;
    }
private:
    string name; //道具名称
    int price; //道具价格
    int effect; //道具效果
};

//定义玩家类
class Player {
public:
    //构造函数，初始化玩家的生命、攻击、防御、金钱、背包
    Player(double life, int attack, int defense, int money) {
        this->life = life;
        this->attack = attack;
        this->defense = defense;
        this->money = money;
        for (int i = 0; i < 10; i++) {
            bag[i] = NULL; //背包为空
        }
    }
    //获取玩家的生命
    double getLife() {
        return life;
    }
    //获取玩家的攻击
    int getAttack() {
        return attack;
    }
    //获取玩家的防御
    int getDefense() {
        return defense;
    }
    //获取玩家的金钱
    int getMoney() {
        return money;
    }
    //设置玩家的生命
    void setLife(double life) {
        this->life = life;
    }
    //设置玩家的攻击
    void setAttack(int attack) {
        this->attack = attack;
    }
    //设置玩家的防御
    void setDefense(int defense) {
        this->defense = defense;
    }
    //设置玩家的金钱
    void setMoney(int money) {
        this->money = money;
    }
    //获取玩家的背包
    Item** getBag() {
        return bag;
    }
    //购买道具，参数为道具对象和数量
    void buyItem(Item* item, int number) {
        if (item == NULL || number <= 0) { //参数无效
            cout << "无效的购买请求！" << endl;
            return;
        }
        int total_price = item->getPrice() * number; //计算总价
        if (money < total_price) { //金钱不足
            cout << "你没有足够的金钱购买" << item->getName() << "！" << endl;
            return;
        }
        money -= total_price; //扣除金钱
        cout << "你花了" << total_price << "元购买了" << number << "个" << item->getName() << "！" << endl;
        for (int i = 0; i < 10; i++) { //遍历背包，寻找空位存放道具
            if (bag[i] == NULL) {
                bag[i] = item; //存放道具
                break;
            }
        }
    }

    //使用道具，参数为道具对象和怪物对象指针（如果有）
    void useItem(Item* item, int* monster_attack, int* monster_defense) {
        if (item == NULL) { //参数无效
            cout << "无效的使用请求！" << endl;
            return;
        }
        cout << "你使用了" << item->getName() << "！" << endl;
        switch (item->getEffect()) { //根据道具效果执行不同操作
        case 1: //增加生命值
            life += 50;
            cout << "你的生命值增加了50点！" << endl;
            break;
        case 2: //增加攻击力
            attack += 10;
            cout << "你的攻击力增加了10点！" << endl;
            break;
        case 3: //增加防御力
            defense += 10;
            cout << "你的防御力增加了10点！" << endl;
            break;
        case 4: //减少怪物攻击力
            if (monster_attack == NULL) { //参数无效
                cout << "没有怪物可以使用这个道具！" << endl;
                return;
            }
            *monster_attack -= 10;
            cout << "怪物的攻击力减少了10点！" << endl;
            break;
        case 5: //减少怪物防御力
            if (monster_defense == NULL) { //参数无效
                cout << "没有怪物可以使用这个道具！" << endl;
                return;
            }
            *monster_defense -= 10;
            cout << "怪物的防御力减少了10点！" << endl;
            break;
        default: //无效的效果
            cout << "这个道具没有任何效果！" << endl;
        }
        for (int i = 0; i < 10; i++) { //遍历背包，寻找道具位置
            if (bag[i] == item) {
                bag[i] = NULL; //移除道具
                break;
            }
        }
    }

    //显示玩家的状态
    void showStatus() {
        cout << "你的生命值：" << life << endl;
        cout << "你的攻击力：" << attack << endl;
        cout << "你的防御力：" << defense << endl;
        cout << "你的金钱：" << money << endl;
    }

    //显示玩家的背包
    void showBag() {
        cout << "你的背包：" << endl;
        for (int i = 0; i < 10; i++) {
            if (bag[i] != NULL) { //如果有道具，显示其名称和价格
                cout << i + 1 << ". " << bag[i]->getName()
                    << "（价格：" << bag[i]->getPrice()
                    << "）" << endl;
            }
            else { //如果没有道具，显示空位
                cout << i + 1 << ". 空" << endl;
            }
        }
    }

private:
    double life; //生命值
    int attack; //攻击力
    int defense; //防御力
    int money; //金钱
    Item* bag[10]; //背包，最多存放10个道具
};

//定义商店类
class Shop {
public:
    //构造函数，初始化商店的名称和商品列表
    Shop(string name, Item* items[], int size) {
        this->name = name;
        this->items = items;
        this->size = size;
    }
    //获取商店的名称
    string getName() {
        return name;
    }
    //获取商店的商品列表
    Item** getItems() {
        return items;
    }
    //获取商店的商品数量
    int getSize() {
        return size;
    }
private:
    string name; //商店名称
    Item** items; //商品列表，指向道具对象的指针数组
    int size; //商品数量
};

//定义打开商店系统的按钮类
class ShopButton {
public:
    //构造函数，初始化按钮的名称和关联的商店对象指针
    ShopButton(string name, Shop* shop) {
        this->name = name;
        this->shop = shop;
    }
    //获取按钮的名称
    string getName() {
        return name;
    }
    //获取按钮关联的商店对象指针
    Shop* getShop() {
        return shop;
    }
private:
    string name; //按钮名称
    Shop* shop; //关联的商店对象指针
};

//定义打开商店系统的函数，参数为玩家和怪物对象指针（如果有）
void openShopSystem(Player* player, int* monster_attack, int* monster_defense) {
    if (player == NULL) { //参数无效
        cout << "无效的玩家对象！" << endl;
        return;
    }
    //创建商店对象和道具对象    
    Item* item1 = new Item("生命药水", 10, 1); //效果为增加生命值
    Item* item2 = new Item("攻击药水", 20, 2); //效果为增加攻击力
    Item* item3 = new Item("防御药水", 20, 3); //效果为增加防御力
    Item* item4 = new Item("破甲弹", 30, 4); //效果为减少怪物攻击力
    Item* item5 = new Item("破盾弹", 30, 5); //效果为减少怪物防御力
    Item* items[5] = { item1, item2, item3, item4, item5 }; //商品列表
    Shop* shop = new Shop("必应商店", items, 5); //商店对象

    //创建商店按钮对象
    ShopButton* button = new ShopButton("打开商店", shop);

    //显示按钮名称
    cout << "你看到了一个按钮，上面写着：" << button->getName() << endl;

    //询问是否按下按钮
    cout << "你是否要按下这个按钮？（y/n）" << endl;
    char choice;
    cin >> choice;

    if (choice == 'y' || choice == 'Y') { //如果选择按下按钮
        cout << "你按下了这个按钮，" << button->getShop()->getName() << "打开了！" << endl;
        bool exit = false; //是否退出商店的标志
        while (!exit) { //循环直到退出商店
            //显示玩家的状态和背包
            player->showStatus();
            player->showBag();

            //显示商店的商品列表
            cout << button->getShop()->getName() << "的商品列表：" << endl;
            for (int i = 0; i < button->getShop()->getSize(); i++) {
                cout << i + 1 << ". " << button->getShop()->getItems()[i]->getName()
                    << "（价格：" << button->getShop()->getItems()[i]->getPrice()
                    << "）" << endl;
            }
            cout << "0. 退出商店" << endl;

            //询问是否购买或使用商品
            cout << "你是否要购买或使用商品？（b/u/n）" << endl;
            cin >> choice;

            if (choice == 'b' || choice == 'B') { //如果选择购买商品
                int index; //商品序号
                int number; //商品数量
                cout << "请输入你要购买的商品序号（1-5）：" << endl;
                cin >> index;
                if (index < 1 || index > 5) { //序号无效
                    cout << "无效的商品序号！" << endl;
                    continue;
                }
                cout << "请输入你要购买的商品数量：" << endl;
                cin >> number;
                if (number <= 0) { //数量无效
                    cout << "无效的商品数量！" << endl;
                    continue;
                }
                player->buyItem(button->getShop()->getItems()[index - 1], number); //玩家购买商品
            }
            else if (choice == 'u' || choice == 'U') { //如果选择使用商品
                int index; //商品序号
                cout << "请输入你要使用的商品序号（1-10）：" << endl;
                cin >> index;
                if (index < 1 || index > 10) { //序号无效
                    cout << "无效的商品序号！" << endl;
                    continue;
                }
                player->useItem(player->getBag()[index - 1], monster_attack, monster_defense); //玩家使用商品
            }
            else if (choice == 'n' || choice == 'N') { //如果选择不购买或使用商品
                exit = true; //退出商店
                cout << "你离开了" << button->getShop()->getName() << "！"
                    << endl;
            }
            else { //无效的输入
                cout << "无效的输入！"
                    << endl;
            }
        }
    }
    else if (choice == 'n' || choice == 'N') { //如果选择不按下按钮
        cout << "你没有按下这个按钮，" << button->getShop()->getName() << "没有打开！" << endl;
    }
    else { //无效的输入
        cout << "无效的输入！" << endl;
    }
}

//主函数，测试代码
int main() {
    //创建玩家对象
    Player* player = new Player(100, 20, 10, 100);

    //创建怪物对象指针，用于模拟怪物的攻击力和防御力
    int monster_attack = 30;
    int monster_defense = 20;

    //打开商店系统
    openShopSystem(player, &monster_attack, &monster_defense);

    return 0;
}
