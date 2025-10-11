#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>

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
     * Reason: <Reason>, (Type of failure- logical, code, network and e.t.c)
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
    public:
        Message(std::string ResponseTo, std::string Producer);
        void setStatus(int status); // adds new flags to StatusCode
        int getStatusCode();
        void setReason(std::string reason);
        void setDetails(std::string details);
        void setAdvice(std::string advice);
        void setBooleanStatus(bool flag);
        std::string getFormattedMessage();
        std::map<std::string, std::string> getDict();
        bool getBooleanStatus()
        {
            return this->status;
        }
};

#endif // MESSAGE_H
