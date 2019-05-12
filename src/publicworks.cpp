#include <eosio/eosio.hpp>

using namespace eosio;

class [[eosio::contract("publicworks")]] publicworks : public eosio::contract {

public:
  using contract::contract;
  
  publicworks(name receiver, name code,  datastream<const char*> ds): contract(receiver, code, ds) {}

  [[eosio::action]]
  void create(name user, std::string title, std::string description, int jobs, float cost, std::string completion, int id, std::string image, std::string address) {
    require_auth( user );
    address_index addresses( get_self(), get_first_receiver().value );
    auto iterator = addresses.find(user.value);
    if( iterator == addresses.end() )
    {
      addresses.emplace(user, [&]( auto& row ) {
       row.key = user;
       row.title = title;
       row.description = description;
       row.jobs = jobs;
       row.cost = cost;
       row.completion = completion;
       row.id = id;
       row.image = image;
       row.votes = 0;
       row.address = address;
      });
    }
  }

  [[eosio::action]]
  void upvote(int id, name sender) {
    address_index addresses( get_self(), get_first_receiver().value );
    auto iterator = addresses.find(id);
    addresses.modify(iterator, sender, [&]( auto& row ) {
        row.votes++;
      });
  }
  
  [[eosio::action]]
  void downvote(int id, name sender) {
    address_index addresses( get_self(), get_first_receiver().value );
    auto iterator = addresses.find(id);
    addresses.modify(iterator, sender, [&]( auto& row ) {
        row.votes--;
      });
  }
  

  [[eosio::action]]
  void erase(int id) {
    address_index addresses( get_self(), get_first_receiver().value);

    auto iterator = addresses.find(id);
    check(iterator != addresses.end(), "Record does not exist");
    //require_auth(iterator->key);
    addresses.erase(iterator);
  }
  

private:
  struct [[eosio::table]] proposal {
    name key;
    std::string title;
    std::string description;
    int jobs;
    float cost;
    std::string completion;
    std::string image;
    int id;
    int votes;
    std::string address;
    uint64_t primary_key() const { return id; }
  };
  typedef eosio::multi_index<"proposals"_n, proposal> address_index;

};
