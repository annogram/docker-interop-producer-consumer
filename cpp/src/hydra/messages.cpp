#include "messages.h"

hydra::Message::Message(std::string path, std::string sender) : _path(path), _sender(sender) {

}

std::unique_ptr<hydra::Message> hydra::Message::ParseMessage(std::string raw) {
    rapidjson::Document parsedMessage;
    parsedMessage.Parse(raw.c_str());
    auto type = parsedMessage["type"].GetString(),
        path = parsedMessage["path"].GetString(),
        uuid = parsedMessage["sender"].GetString();

    if (type == "GET"){
        return std::unique_ptr<hydra::Message>{new hydra::Get(path, uuid)};
    } else if (type == "DELETE") {
        return std::unique_ptr<hydra::Message>{new hydra::Delete(path, uuid)};
    } else if (type == "POST") {
        auto data = parsedMessage["data"].GetString();
        return std::unique_ptr<hydra::Message>{new hydra::Post(path, uuid, data)};
    } else if (type == "PUT") {
        auto data = parsedMessage["data"].GetString();
        return std::unique_ptr<hydra::Message>{new hydra::Put(path, uuid, data)};
    }
}