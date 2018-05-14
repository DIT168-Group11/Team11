#ifndef V2V_PROTOCOL_DEMO_V2VSERVICE_H
#define V2V_PROTOCOL_DEMO_V2VSERVICE_H

#include <iomanip>
#include <queue>
#include <chrono>
#include <unistd.h>
#include <sys/time.h>
#include "cluon/OD4Session.hpp"
#include "cluon/UDPSender.hpp"
#include "cluon/UDPReceiver.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"
#include <iostream>

/** ADD YOUR CAR_IP AND GROUP_ID HERE:  *****************/

// static const std::string YOUR_CAR_IP    = "172.20.10.13";
// static const std::string YOUR_GROUP_ID  = "11";

/********************************************************/
/** DON'T CHANGE STUFF BELOW THIS LINE. *****************/
/********************************************************/

static const int BROADCAST_CHANNEL = 250;
static const int DEFAULT_PORT = 50001;

static const int ANNOUNCE_PRESENCE = 1001;
static const int FOLLOW_REQUEST = 1002;
static const int FOLLOW_RESPONSE = 1003;
static const int STOP_FOLLOW = 1004;
static const int LEADER_STATUS = 2001;
static const int FOLLOWER_STATUS = 3001;

static const int GROUND_STEERING_READING = 1045;
static const int PEDAL_POSITION_READING = 1041;

class V2VService {
public:
    std::map <std::string, std::string> presentCars;

    V2VService(std::string carIP, std::string groupID);

    void announcePresence();
    void followRequest(std::string vehicleIp);
    void followResponse();
    void stopFollow(std::string vehicleIp);
    void leaderStatus(float speed, float steeringAngle, uint8_t distanceTraveled);
    void followerStatus();

    std::string getIPfromID(std::string id);

    std::queue<LeaderStatus> commandQ;


private:
    std::string carIp;
    std::string groupId;
    std::string leaderIp;
    std::string followerIp;

    std::shared_ptr<cluon::OD4Session>  broadcast;
    std::shared_ptr<cluon::UDPReceiver> incoming;
    std::shared_ptr<cluon::UDPSender>   toLeader;
    std::shared_ptr<cluon::UDPSender>   toFollower;


    static uint32_t getTime();
    static std::pair<int16_t, std::string> extract(std::string data);
    template <class T>
    static std::string encode(T msg);
    template <class T>
    static T decode(std::string data);
};

#endif //V2V_PROTOCOL_DEMO_V2VSERVICE_H
