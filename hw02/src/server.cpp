/**
 * file server.cpp
 * fetch150zy (Mars_zhewei@outlook.com)
 * date 2023-04-27 
 * copyleft Copyleft (ɔ) 2023 
 */
#include "server.h"

#include <random>
#include <iostream>
#include <regex>
#include <algorithm>

std::vector<std::string> pending_trxs;

Server::Server() { }

std::shared_ptr<Client> Server::add_client(std::string id)
{
    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_real_distribution<double> uniform_dist(1000, 9999);
    for (const auto& client: clients)
        if (client.first->get_id() == id)
            id += std::to_string(uniform_dist(e));
    std::shared_ptr<Client> client = std::make_shared<Client>(id, *this);
    clients.insert({client, 5.0});
    return client;
}

std::shared_ptr<Client> Server::get_client(std::string id) const
{
    for (const auto& client: clients)
        if (client.first->get_id() == id)
            return client.first;
    return nullptr;
}

double Server::get_wallet(std::string id) const
{
    for (const auto &client: clients)
        if (client.first->get_id() == id)
            return client.second;
    return 0;
}

bool Server::parse_trx(const std::string& trx, std::string& sender, 
                        std::string& receiver, double& value)
{
    std::string pattern = R"((\w+)-(\w+)-(\d+\.\d+))";
	std::regex r(pattern);
	std::smatch results;
	if (std::regex_match(trx, results, r)) {
		sender = results.str(1);
		receiver = results.str(2);
		value = std::stod(results.str(3));
		return true;
	} else {
		throw std::runtime_error("something wrong in match trx");
	}
	return false;
}

bool Server::add_pending_trx(std::string trx, std::string signature) const
{
    std::string sender{}, receiver{};
    double value = 0.0;
    parse_trx(trx, sender, receiver, value);
    std::shared_ptr<Client> sender_ptr = get_client(sender);
    std::shared_ptr<Client> receiver_ptr = get_client(receiver);
    if (nullptr == receiver_ptr)
        return false;

    bool authentic = crypto::verifySignature(sender_ptr->get_publickey(), 
                            trx, signature);
    if (authentic && value <= clients.at(sender_ptr)) {
        pending_trxs.push_back(trx);
        return true;
    }
    return false;
}

size_t Server::mine()
{
    std::string mempool = std::accumulate(pending_trxs.cbegin(),
                pending_trxs.cend(), std::string{});
    size_t nonce = 0;
	bool flag = false;  //not mined
	while (!flag) {
		for (auto& client : clients) {
			nonce = client.first->generate_nonce();
			if (crypto::sha256(mempool + std::to_string(nonce))
                                            .substr(0, 10)
                                            .find("000") != std::string::npos) {   //mined
                flag = true;
				client.second += 6.25;
				for (const auto& trx : pending_trxs) {
					std::string sender, receiver;
					double value;
					Server::parse_trx(trx, sender, receiver, value);
					clients[get_client(sender)] -= value;
					clients[get_client(receiver)] += value;
				}
				pending_trxs.clear();
                return nonce;
			}
		}
	}
	return nonce;
}

void show_wallets(const Server& server)
{
    std::cout << std::string(20, '*') << std::endl;
    auto hack_server = *((std::map<std::shared_ptr<Client>, double>*)(&server));
    for(const auto& client: hack_server)
        std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
    std::cout << std::string(20, '*') << std::endl;
}