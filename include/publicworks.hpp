#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

CONTRACT publicworks : public contract {
  public:
    using contract::contract;
    pollinate(eosio::name receiver, eosio::name code, datastream<const char*> ds):contract(receiver, code, ds) {}

    ACTION create(name user, std::string first_name, std::string last_name, float startLatitude, float startLongitude, float endLatitude, float endLongitude, int id, float reward)
  
  private:
    TABLE tableStruct {
      name key;
      std::string name;
    };
    typedef eosio::multi_index<"table"_n, tableStruct> table;
};

EOSIO_DISPATCH(pollinate, (hi))
