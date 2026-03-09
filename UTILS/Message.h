#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>
#include <map>
#include <stdint.h>
namespace UTILS {

namespace statusMaps
{
const int STATUS_OK = 0;
const int WARNING = 1;
const int FAILURE = 2;
const int CRIT_FAILURE = 4;
}

class Message
{
    /*
     * Message format
     * Producer: <ProducerName>, (Entity who performed action)
     * ------------------------
     * Parent: <ResponseTo>, (Which entity created task, or the command)
     * -----------------------
     * Code of operations: <Status> (OK or War|Fail|CritFail)
     * -----------------------
     * Reason: <Reason>, (Type of failure: logical, code, network and e.t.c)
     * -----------------------
     * Details: <Details> (Details about failure)
     * -----------------------
     * Advice: <Advice> (What to do to fix or avoid or why are you wrong)
     */
private:
    bool status = true;
    std::string ProducerName;
    std::string ResponseTo;
    int StatusCode = statusMaps::STATUS_OK;
    std::string Reason;
    std::string Details;
    std::string Advice;
    std::string messageType; // is not displayed and used only for event bus (in future)

public:
    // Constructor – all parameters are mandatory
    Message(std::string ResponseTo, std::string Producer, std::string messageType)
        : ResponseTo(ResponseTo),
        ProducerName(Producer),
        status(false),
        StatusCode(statusMaps::STATUS_OK),
        messageType(messageType)
    {}

    // Add new flags to StatusCode using bitwise OR
    void setStatus(int newStatus) {
        StatusCode |= newStatus;
    }

    int getStatusCode() {
        return StatusCode;
    }

    void setReason(std::string reason) {
        Reason = reason;
    }

    void setDetails(std::string details) {
        Details = details;
    }

    void setAdvice(std::string advice) {
        Advice = advice;
    }

    void setBooleanStatus(bool flag) {
        status = flag;
    }

    // Return formatted message as plain text
    std::string getFormattedMessage() {
        std::string formatted;
        formatted += "Producer: " + ProducerName + "\n";
        formatted += "------------------------\n";
        formatted += "Parent: " + ResponseTo + "\n";
        formatted += "------------------------\n";

        // Decode StatusCode bits
        formatted += "Code of operations: ";
        if (StatusCode == statusMaps::STATUS_OK) {
            formatted += "OK";
        } else {
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
    std::map<std::string, std::string> getDict() {
        std::map<std::string, std::string> dict;
        dict["Producer"] = ProducerName;
        dict["Parent"] = ResponseTo;

        // Store numeric code
        dict["Code"] = std::to_string(StatusCode);

        // Store text representation for convenience
        if (StatusCode == statusMaps::STATUS_OK)
            dict["CodeText"] = "OK";
        else {
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

    std::string getType() {
        return this->messageType;
    }

    bool getBooleanStatus() {
        return this->status;
    }
};

} // namespace UTILS

#endif // MESSAGE_H
