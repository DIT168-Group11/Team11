#include "V2VService.hpp"

opendlv::proxy::GroundSteeringReading msgSteering;
opendlv::proxy::PedalPositionReading msgPedal;

int main(int argc, char **argv) {

    auto externalArguments = cluon::getCommandlineArguments(argc, argv); 
    const uint16_t freq = (uint16_t) std::stoi(externalArguments["freq"]);
    const bool followerStat = false; //IF TRUE CAR IS FOLLOWER IS FALSE CAR IS LEADER
    const std::string carIP = externalArguments["ip"];
    
    //ID OF THE LEADER CAR
    const std::string leaderId = "3";
    float speed = 0;
    float angle = 0;
    float remote_distance = 50;
    float remote_speed = 0;
    float remote_angle = 0;
    static int cunt = 0;
    static float steer = 1;
  
    std::shared_ptr<V2VService> v2v_Communication = std::make_shared<V2VService>(carIP, "11");
	    
    //FETCH THE VARIABLES FROM THE CAR AND ASSIGN THEM TO VARIABLES
    cluon::OD4Session od4(220, [&speed, &angle](cluon::data::Envelope &&envelope) noexcept {
        if (envelope.dataType() == opendlv::proxy::PedalPositionReading::ID()) {
            opendlv::proxy::PedalPositionReading pedalPositionReading =
                cluon::extractMessage<opendlv::proxy::PedalPositionReading>(std::move(envelope));
            speed = pedalPositionReading.position();
        }
        if (envelope.dataType() == opendlv::proxy::GroundSteeringReading::ID()) {
            opendlv::proxy::GroundSteeringReading groundSteeringReading =
                cluon::extractMessage<opendlv::proxy::GroundSteeringReading>(std::move(envelope));
            angle = groundSteeringReading.groundSteering();
        }
       
    });

    //GETTING MSGs FROM THE REMOTE CONTROL, AND ASSIGN THEM TO VARIABLES
    cluon::OD4Session od4_remote(221,[&remote_speed, &remote_angle, &remote_distance](cluon::data::Envelope &&envelope) noexcept {
        if (envelope.dataType() == opendlv::proxy::PedalPositionReading::ID()) {
            opendlv::proxy::PedalPositionReading remoteSpeedMsg = cluon::extractMessage<opendlv::proxy::PedalPositionReading>(std::move(envelope));
            remote_speed = remoteSpeedMsg.position();
        }
        if (envelope.dataType() == opendlv::proxy::GroundSteeringReading::ID()) {
            opendlv::proxy::GroundSteeringReading remoteAngleMsg = cluon::extractMessage<opendlv::proxy::GroundSteeringReading>(std::move(envelope));
            remote_angle = remoteAngleMsg.groundSteering();
        }
        if (envelope.dataType() == opendlv::proxy::DistanceReading::ID()) {
            opendlv::proxy::DistanceReading remoteDistanceMsg = 
                cluon::extractMessage<opendlv::proxy::DistanceReading>(std::move(envelope));
            remote_distance = remoteDistanceMsg.distance();
        }
    });

    

    //FUNCTION THAT PERFORMS ANNOUNCE PRESENCE AND LEADER STATUS
    
    //IF A CAR IP IS REGISTERED, LEADER STATUS WILL RUN, AND ANNOUNCE PRESENCE WON'T -- and VICE-VERSA
    //FETCHES THE LATEST CAR SPEED AND STEERING ANGLE VALUES, AND DECIDES WHICH ONES TO SEND.
    auto v2v{[&v2v_Communication, &speed, &angle, &remote_speed, &remote_angle, &remote_distance, &followerStat, &leaderId, &od4_remote, &od4]() -> bool {

    	opendlv::proxy::GroundSteeringReading msgAngle;
        opendlv::proxy::PedalPositionReading msgSpeed;

        v2v_Communication->announcePresence();
        //GETTING THE IP FROM THE LEADER
        std::string leaderIp = v2v_Communication->getIp(leaderId);
        
        // STOP IF DISTANCE IS LESS THAN WHAT WE WANT
        if(0.22 >= remote_distance){
            // STOPS THE CAR
            msgPedal.position(0.0);
            od4_remote.send(msgPedal);
            
        }else{
            //SEND THE VALUES FROM THE REMOTE CONTROL TO THE PROXY
            msgPedal.position(remote_speed);
            od4_remote.send(msgPedal);
            msgSteering.groundSteering(remote_angle);
            od4_remote.send(msgSteering);
        }
  
        //CHECK FOR LEADER OR FOLLOWER STATUS
        if(followerStat){
            //SEND FOLLOW REQUEST AFTER ANNOUNCE PRESENCE
            v2v_Communication->followRequest(leaderIp);
            v2v_Communication->followerStatus();
 
            //GET MESSAGES QUEUE
            if(!v2v_Communication->commandQ.empty()){

            	float speedIncrease = 0.01;
                float recievedAngle = v2v_Communication->commandQ.front().steeringAngle();
                float recievedSpeed = v2v_Communication->commandQ.front().speed();

				if(steer != recievedAngle){
                	//INCREMENT COUNTER THAT ALLOWS FOR FOLLOWING DELAY
                	cunt++;
                }

                if(recievedSpeed != 0){
                	//CHANGES THE SPEED ACCORDING TO THE LEADER's SPEED
                	recievedSpeed += speedIncrease;
                }
                

                if(22 <= cunt){
                	//START EXECUTION OF COMMANDS WHEN LIMIT IS REACHED
                	msgAngle.groundSteering(recievedAngle);
                	od4.send(msgAngle);
                	steer = recievedAngle;
                	cunt = 0;
                }

                msgSpeed.position(recievedSpeed);
                od4.send(msgSpeed);
            }else{
                //STOP CAR IF NO COMMANDS ARE RECEIVED
                msgSpeed.position(0.0);
                od4.send(msgSpeed);
            }

        }else{
        	//DEFAULT ACTION
        	msgAngle.groundSteering(remote_angle);
        	od4.send(msgAngle);
        	msgSpeed.position(remote_speed);
        	od4.send(msgSpeed);
            v2v_Communication->leaderStatus(remote_speed, remote_angle, 11);
            
        }
        return true;
    }};

    //REPEAT THE FUNCTION ACCORDING TO FREQ
    od4.timeTrigger(freq, v2v);
}

/**
 * Implementation of the V2VService class as declared in V2VService.hpp
 */
V2VService::V2VService(std::string carIP, std::string groupID) {
    /*
     * The broadcast field contains a reference to the broadcast channel which is an OD4Session. This is where
     * AnnouncePresence messages will be received.
     */
    carIp = carIP;
    groupId = groupID;

    broadcast =

            std::make_shared<cluon::OD4Session>(BROADCAST_CHANNEL,
                                                [this](cluon::data::Envelope &&envelope) noexcept {
                                                    std::cout << "[OD4] ";
                                                    switch (envelope.dataType()) {
                                                        case ANNOUNCE_PRESENCE: {
                                                            AnnouncePresence ap = cluon::extractMessage<AnnouncePresence>(std::move(envelope));
                                                            std::cout << "received 'AnnouncePresence' from '"
                                                                      << ap.vehicleIp() << "', GroupID '"
                                                                      << ap.groupId() << "'!" << std::endl;

                                                            presentCars[ap.groupId()] = ap.vehicleIp();

                                                            break;
                                                        }
                                                        default: std::cout << "¯\\_(ツ)_/¯" << std::endl;
                                                    }
                                                });


    /*
     * Each car declares an incoming UDPReceiver for messages directed at them specifically. This is where messages
     * such as FollowRequest, FollowResponse, StopFollow, etc. are received.
     */
    incoming =
            std::make_shared<cluon::UDPReceiver>("0.0.0.0", DEFAULT_PORT,
                                                 [this](std::string &&data, std::string &&sender, std::chrono::system_clock::time_point &&ts) noexcept {
                                                     std::cout << "[UDP] ";
                                                     std::pair<int16_t, std::string> msg = extract(data);

                                                     switch (msg.first) {
                                                         case FOLLOW_REQUEST: {
                                                             FollowRequest followRequest = decode<FollowRequest>(msg.second);
                                                             std::cout << "received '" << followRequest.LongName()
                                                                       << "' from '" << sender << "'!" << std::endl;

                                                             // After receiving a FollowRequest, check first if there is currently no car already following.
                                                             if (followerIp.empty()) {
                                                                 unsigned long len = sender.find(':');    // If no, add the requester to known follower slot
                                                                 followerIp = sender.substr(0, len);      // and establish a sending channel.
                                                                 toFollower = std::make_shared<cluon::UDPSender>(followerIp, DEFAULT_PORT);
                                                                 followResponse();
                                                             }
                                                             break;
                                                         }
                                                         case FOLLOW_RESPONSE: {
                                                             FollowResponse followResponse = decode<FollowResponse>(msg.second);
                                                             std::cout << "received '" << followResponse.LongName()
                                                                       << "' from '" << sender << "'!" << std::endl;
                                                             break;
                                                         }
                                                         case STOP_FOLLOW: {
                                                             StopFollow stopFollow = decode<StopFollow>(msg.second);
                                                             std::cout << "received '" << stopFollow.LongName()
                                                                       << "' from '" << sender << "'!" << std::endl;

                                                             // Clear either follower or leader slot, depending on current role.
                                                             unsigned long len = sender.find(':');
                                                             if (sender.substr(0, len) == followerIp) {
                                                                 followerIp = "";
                                                                 toFollower.reset();
                                                             }
                                                             else if (sender.substr(0, len) == leaderIp) {
                                                                 leaderIp = "";
                                                                 toLeader.reset();
                                                             }
                                                             break;
                                                         }
                                                         case FOLLOWER_STATUS: {
                                                             FollowerStatus followerStatus = decode<FollowerStatus>(msg.second);
                                                             std::cout << "received '" << followerStatus.LongName()
                                                                       << "' from '" << sender << "'!" << std::endl;


                                                             break;
                                                         }
                                                         case LEADER_STATUS: {
                                                             LeaderStatus leaderStatus = decode<LeaderStatus>(msg.second);
                                                             std::cout << "received '" << leaderStatus.LongName()
                                                                       << "' from '" << sender << " Speed: "
                                                                       << leaderStatus.speed() << " Angle: "
                                                                       << leaderStatus.steeringAngle() << std::endl;

                                                            // float leader_angle = leaderStatus.steeringAngle();
                                                            // float leader_speed = leaderStatus.speed();

                                                             commandQ.push(leaderStatus);

                                                             break;
                                                         }
                                                         default: std::cout << "¯\\_(ツ)_/¯" << std::endl;
                                                     }
                                                 });
}

/**
 * This function sends an AnnouncePresence (id = 1001) message on the broadcast channel. It will contain information
 * about the sending vehicle, including: IP, port and the group identifier.
 */
void V2VService::announcePresence() {
    if (!followerIp.empty() || !leaderIp.empty()) return;
    AnnouncePresence announcePresence;
    announcePresence.vehicleIp(carIp);
    announcePresence.groupId(groupId);
    broadcast->send(announcePresence);
}

/**
 * This function sends a FollowRequest (id = 1002) message to the IP address specified by the parameter vehicleIp. And
 * sets the current leaderIp field of the sending vehicle to that of the target of the request.
 *
 * @param vehicleIp - IP of the target for the FollowRequest
 */
void V2VService::followRequest(std::string vehicleIp) {
    if (!leaderIp.empty()) return;
    std::cout << "SENDING FOLLOW REQUEST TO: " << vehicleIp << std::endl;
    leaderIp = vehicleIp;
    toLeader = std::make_shared<cluon::UDPSender>(leaderIp, DEFAULT_PORT);
    FollowRequest followRequest;
    toLeader->send(encode(followRequest));
}

/**
 * This function send a FollowResponse (id = 1003) message and is sent in response to a FollowRequest (id = 1002).
 * This message will contain the NTP server IP for time synchronization between the target and the sender.
 */
void V2VService::followResponse() {
    if (followerIp.empty()) return;
    FollowResponse followResponse;
    toFollower->send(encode(followResponse));
}

/**
 * This function sends a StopFollow (id = 1004) request on the ip address of the parameter vehicleIp. If the IP address is neither
 * that of the follower nor the leader, this function ends without sending the request message.
 *
 * @param vehicleIp - IP of the target for the request
 */
void V2VService::stopFollow(std::string vehicleIp) {
    StopFollow stopFollow;
    if (vehicleIp == leaderIp) {
        toLeader->send(encode(stopFollow));
        leaderIp = "";
        toLeader.reset();
    }
    if (vehicleIp == followerIp) {
        toFollower->send(encode(stopFollow));
        followerIp = "";
        toFollower.reset();
    }
}

/**
 * This function sends a FollowerStatus (id = 3001) message on the leader channel.
 *
 * @param speed - current velocity
 * @param steeringAngle - current steering angle
 * @param distanceFront - distance to nearest object in front of the car sending the status message
 * @param distanceTraveled - distance traveled since last reading
 */
void V2VService::followerStatus() {
    if (leaderIp.empty()) return;
    FollowerStatus followerStatus;
    toLeader->send(encode(followerStatus));
}

/**
 * This function sends a LeaderStatus (id = 2001) message on the follower channel.
 *
 * @param speed - current velocity
 * @param steeringAngle - current steering angle
 * @param distanceTraveled - distance traveled since last reading
 */
void V2VService::leaderStatus(float speed, float steeringAngle, uint8_t distanceTraveled) {
    if (followerIp.empty()) return;
    LeaderStatus leaderStatus;
    leaderStatus.timestamp(getTime());
    leaderStatus.speed(speed);
    leaderStatus.steeringAngle(steeringAngle);
    leaderStatus.distanceTraveled(distanceTraveled);
    toFollower->send(encode(leaderStatus));
}

/**
 * Gets the current time.
 *
 * @return current time in milliseconds
 */
uint32_t V2VService::getTime() {
    timeval now;
    gettimeofday(&now, nullptr);
    return (uint32_t ) now.tv_usec / 1000;
}

/**
 * The extraction function is used to extract the message ID and message data into a pair.
 *
 * @param data - message data to extract header and data from
 * @return pair consisting of the message ID (extracted from the header) and the message data
 */
std::pair<int16_t, std::string> V2VService::extract(std::string data) {
    if (data.length() < 10) return std::pair<int16_t, std::string>(-1, "");
    int id, len;
    std::stringstream ssId(data.substr(0, 4));
    std::stringstream ssLen(data.substr(4, 10));
    ssId >> std::hex >> id;
    ssLen >> std::hex >> len;
    return std::pair<int16_t, std::string> (
            data.length() -10 == len ? id : -1,
            data.substr(10, data.length() -10)
    );
};

/**
 * Generic encode function used to encode a message before it is sent.
 *
 * @tparam T - generic message type
 * @param msg - message to encode
 * @return encoded message
 */
template <class T>
std::string V2VService::encode(T msg) {
    cluon::ToProtoVisitor v;
    msg.accept(v);
    std::stringstream buff;
    buff << std::hex << std::setfill('0')
         << std::setw(4) << msg.ID()
         << std::setw(6) << v.encodedData().length()
         << v.encodedData();
    return buff.str();
}

/**
 * Generic decode function used to decode an incoming message.
 *
 * @tparam T - generic message type
 * @param data - encoded message data
 * @return decoded message
 */
template <class T>
T V2VService::decode(std::string data) {
    std::stringstream buff(data);
    cluon::FromProtoVisitor v;
    v.decodeFrom(buff);
    T tmp = T();
    tmp.accept(v);
    return tmp;
}

std::string V2VService::getIp(std::string id){
    //std::cout << "IP IS" << presentCars[id] << std::endl;
    return presentCars[id];
}

