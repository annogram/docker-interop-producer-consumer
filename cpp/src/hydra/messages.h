#if !defined(MESSAGES_H)
#define MESSAGES_H

#include <string>
#include <vector>
#include <memory>
#include "../rapidjson/document.h"

namespace hydra
{

enum class MessageType {
    GET, DELETE, POST, PUT
};

class Message
{
protected:
    std::string _sender;
    std::vector<std::string> parameters;
    std::string _path;
    Message(std::string path, std::string sender);
public:
    MessageType type;
    static std::unique_ptr<Message> ParseMessage(std::string message);
    ~Message() {};
};

class Get : public Message
{
public:
    Get(std::string path, std::string sender) : Message(path, sender)
    {
        type = MessageType::GET;
    }
    ~Get() {}
};

class Delete : public Message
{
public:
    Delete(std::string path, std::string sender) : Message(path, sender)
    {
        type = MessageType::DELETE;
    }
    ~Delete() {}
};

class Put : public Message
{
protected:
    rapidjson::Document data;

public:
    Put(std::string path, std::string sender, std::string incoming) : Message(path, sender)
    {
        type = MessageType::PUT;
        data.Parse(incoming.c_str());
    }
    ~Put() {}
};

class Post : public Message
{
protected:
    rapidjson::Document data;

public:
    Post(std::string path, std::string sender, std::string incoming) : Message(path, sender)
    {
        type = MessageType::POST;
        data.Parse(incoming.c_str());
    }
    ~Post() {}
};
} // namespace hydra
#endif // MESSAGES_H
