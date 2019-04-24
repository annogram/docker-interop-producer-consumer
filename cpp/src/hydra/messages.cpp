#include "messages.h"

hydra::Message::Message(std::string path, std::string sender) : _path(path), _sender(sender)
{
}

hydra::Message::Message(const hydra::Message & message): _path(message._path), _sender(message._sender) {

}

hydra::Message::~Message()
{
}

const hydra::Message hydra::Message::ParseMessage(std::string raw)
{
    rapidjson::Document parsedMessage;
    parsedMessage.Parse(raw.c_str());
    auto type = parsedMessage["type"].GetString(),
         path = parsedMessage["path"].GetString(),
         uuid = parsedMessage["sender"].GetString();

    Message message(path, uuid);

    if (type == "GET")
    {
        message.type = MessageType::GET;
    }
    else if (type == "DELETE")
    {
        message.type = MessageType::DELETE;
    }
    else if (type == "POST")
    {
        auto data = parsedMessage["data"].GetString();
        message.type = MessageType::POST;
        message.data.Parse(data);
    }
    else if (type == "PUT")
    {
        auto data = parsedMessage["data"].GetString();
        message.type = MessageType::PUT;
        message.data.Parse(data);
    }
    return message;
}