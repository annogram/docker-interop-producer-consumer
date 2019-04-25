#if !defined(MESSAGES_H)
#define MESSAGES_H

#include <string>
#include <vector>
#include <memory>
#include "../rapidjson/document.h"

namespace hydra
{

enum class MessageType
{
    GET,
    DELETE,
    POST,
    PUT
};

class Message
{
public:
    Message(const std::string& path, const std::string& sender);
    Message(const Message& message);
    ~Message();
    std::string _sender;
    std::vector<std::string> parameters;
    std::string _path;
    MessageType type;
    rapidjson::Document data;
    static const Message ParseMessage(const std::string& message);
};
} // namespace hydra
#endif // MESSAGES_H
