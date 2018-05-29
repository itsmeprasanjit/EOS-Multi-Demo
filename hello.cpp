//
// Created by Admin on 20/05/18.
//

#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace std;
using namespace eosio;

class hello:public contract{
public:
    hello(account_name self ):contract(self){

    }
    /// @abi action
    void hi(account_name user){
        print("hello",name{_self});
    }

    /// @abi action
    void rock(account_name issuer,uint64_t balance){
        customers customer1(_self,issuer);
        customer1.emplace(_self,[&](auto& a){
            a.customer = issuer;
            a.balance = balance;
        });
        print("lets rock it ");
    }

    /// @abi action
    void find(account_name issuer){
        customers customer1(_self,issuer);
        auto targetCustomer = customer1.find(issuer);
        const auto& act = *targetCustomer;
        print("customer balance is:",act.balance);
    }

    /// @abi action
    void change(account_name issuer,uint64_t balance){
        customers customers1(_self,issuer);
        auto targetCustomer = customers1.find(issuer);
        const auto& act = *targetCustomer;
        print("value:",act.customer);
        customers1.modify(targetCustomer,0,[&](auto& a){
            a.balance = balance;
        });

    }

    /// @abi action
    void remove(account_name issuer){
        customers customers1(_self,issuer);
        auto targetCustomer = customers1.find(issuer);
        customers1.erase(targetCustomer);
    };

private:
    struct myCustomer{
        account_name customer;
        uint64_t balance;
        auto primary_key() const {return customer;}
        EOSLIB_SERIALIZE(myCustomer,(customer)(balance))
    };
    typedef multi_index<N(customers),myCustomer> customers;

};

EOSIO_ABI(hello,(hi)(rock)(find)(change)(remove));
