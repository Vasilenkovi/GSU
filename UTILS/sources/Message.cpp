#include "message.h"
#include <map>
#include <string>

Message::Message(std::string ResponseTo = NULL, std::string Producer)
    : ResponseTo(ResponseTo),
    ProducerName(Producer),
    status(false),
    StatusCode(statusMaps::STATUS_OK)
{
}

// Add new flags to StatusCode using bitwise OR
void Message::setStatus(int newStatus)
{
    StatusCode |= newStatus;
}

int Message::getStatusCode()
{
    return StatusCode;
}

void Message::setReason(std::string reason)
{
    Reason = reason;
}

void Message::setDetails(std::string details)
{
    Details = details;
}

void Message::setAdvice(std::string advice)
{
    Advice = advice;
}

void Message::setBooleanStatus(bool flag)
{
    status = flag;
}

// Return formatted message as plain text
std::string Message::getFormattedMessage()
{
    std::string formatted;
    formatted += "Producer: " + ProducerName + "\n";
    formatted += "------------------------\n";
    formatted += "Parent: " + ResponseTo + "\n";
    formatted += "------------------------\n";

    // Decode StatusCode bits
    formatted += "Code of operations: ";
    if (StatusCode == statusMaps::STATUS_OK)
    {
        formatted += "OK";
    }
    else
    {
        bool hasWarning = StatusCode & statusMaps::WARNING;
        bool hasFailure = StatusCode & statusMaps::FAILURE;
        bool hasCritFailure = StatusCode & statusMaps::CRIT_FAILURE;

        bool first = true;
        if (hasWarning) { formatted += "WARNING"; first = false; }
        if (hasFailure) { if (!first) formatted += "|"; formatted += "FAILURE"; first = false; }
        if (hasCritFailure) { if (!first) formatted += "|"; formatted += "CRIT_FAILURE"; }
    }

    formatted += "\n------------------------\n";
    formatted += "Reason: " + Reason + "\n";
    formatted += "------------------------\n";
    formatted += "Details: " + Details + "\n";
    formatted += "------------------------\n";
    formatted += "Advice: " + Advice + "\n";
    formatted += "------------------------\n";
    formatted += "Boolean status: " + std::string(status ? "true" : "false") + "\n";

    return formatted;
}

// Return a map representation of all fields
std::map<std::string, std::string> Message::getDict()
{
    std::map<std::string, std::string> dict;
    dict["Producer"] = ProducerName;
    dict["Parent"] = ResponseTo;

    // Store numeric code
    dict["Code"] = std::to_string(StatusCode);

    // Store text representation for convenience
    if (StatusCode == statusMaps::STATUS_OK)
        dict["CodeText"] = "OK";
    else
    {
        std::string codeText;
        if (StatusCode & statusMaps::WARNING) codeText += "WARNING|";
        if (StatusCode & statusMaps::FAILURE) codeText += "FAILURE|";
        if (StatusCode & statusMaps::CRIT_FAILURE) codeText += "CRIT_FAILURE|";
        if (!codeText.empty() && codeText.back() == '|') codeText.pop_back();
        dict["CodeText"] = codeText;
    }

    dict["Reason"] = Reason;
    dict["Details"] = Details;
    dict["Advice"] = Advice;
    dict["BooleanStatus"] = status ? "true" : "false";

    return dict;
}
