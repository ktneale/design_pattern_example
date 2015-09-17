/*
 * Written by Kevin Neale (C) 2015.
 *
 * Adapted from: https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns/Creational_Patterns
 * Type:  Builder
 * Class: Creational patterns
 */
#include <iostream>

using namespace std;

class Pizza                     //Complex object to build
{
  public:
    void SetDough(const string & dough) {
        m_dough = dough;
    } void SetSauce(const string & sauce) {
        m_sauce = sauce;
    }
    void SetTopping(const string & topping) {
        m_topping = topping;
    }

    void Open() {
        cout << "Pizza with " << m_dough << " dough, " << m_sauce <<
            " sauce and " << m_topping << " topping. Mmm." << endl;
    }

  private:
    string m_dough;
    string m_sauce;
    string m_topping;
};

class PizzaBuilder              //Abstract builder class. Note the pure virtual functions (can't be instantiated!)
{
  public:
    virtual ~ PizzaBuilder() {
    };
    virtual void BuildDough() = 0;
    virtual void BuildSauce() = 0;
    virtual void BuildTopping() = 0;

    Pizza *getPizza() {
        return m_pizza;
    }

    void NewPizzaProduct() {
        m_pizza = new Pizza;
    }

  protected:
    Pizza * m_pizza;
};


class HawaiianPizzaBuilder:public PizzaBuilder {
  public:
    virtual ~ HawaiianPizzaBuilder() {
    };

    virtual void BuildDough() {
        m_pizza->SetDough("cross");
    }

    virtual void BuildSauce() {
        m_pizza->SetSauce("tomato");
    }

    virtual void BuildTopping() {
        m_pizza->SetTopping("Ham+Pineapple");
    }
};

class AmericanHotPizzaBuilder:public PizzaBuilder {
  public:
    virtual ~ AmericanHotPizzaBuilder() {
    };

    virtual void BuildDough() {
        m_pizza->SetDough("thin+crispy");
    }

    virtual void BuildSauce() {
        m_pizza->SetSauce("tomato");
    }

    virtual void BuildTopping() {
        m_pizza->SetTopping("Cheese+Pepperoni+Jalapeno");
    }
};

class Cook {
  public:
    void SetBuilder(PizzaBuilder * builder) {
        m_builder = builder;
    };
    void ConstructPizza() {
        m_builder->NewPizzaProduct();
        m_builder->BuildDough();
        m_builder->BuildSauce();
        m_builder->BuildTopping();
    }

  private:
    PizzaBuilder * m_builder;
};

int main()
{
    Cook cook;

    HawaiianPizzaBuilder *h = new HawaiianPizzaBuilder;
    AmericanHotPizzaBuilder *a = new AmericanHotPizzaBuilder;

    cook.SetBuilder(h);

    cook.ConstructPizza();

    Pizza *p1 = h->getPizza();

    p1->Open();


    cook.SetBuilder(a);

    cook.ConstructPizza();

    Pizza *p2 = a->getPizza();

    p2->Open();

    return 0;
}
