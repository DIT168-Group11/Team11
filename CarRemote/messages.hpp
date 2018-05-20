
/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef VISITABLE_TYPE_TRAIT
#define VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct visitorSelector {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct visitorSelector<true> {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<typename T>
struct isVisitable {
    static const bool value = false;
};

template<typename T, class Visitor>
void doVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
    visitorSelector<isVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, visitor);
}
#endif

#ifndef TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#define TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct tripletForwardVisitorSelector {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)preVisit;
        (void)postVisit;
        std::forward<Visitor>(visit)(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct tripletForwardVisitorSelector<true> {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)fieldIdentifier;
        (void)typeName;
        (void)name;
        // Apply preVisit, visit, and postVisit on value.
        value.accept(preVisit, visit, postVisit);
    }
};

template<typename T>
struct isTripletForwardVisitable {
    static const bool value = false;
};

template< typename T, class PreVisitor, class Visitor, class PostVisitor>
void doTripletForwardVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
    tripletForwardVisitorSelector<isTripletForwardVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, std::move(preVisit), std::move(visit), std::move(postVisit)); // NOLINT
}
#endif


#ifndef OPENDLV_PROXY_GROUNDSTEERINGREADING_HPP
#define OPENDLV_PROXY_GROUNDSTEERINGREADING_HPP

#ifdef WIN32
    // Export symbols if compile flags "LIB_SHARED" and "LIB_EXPORTS" are set on Windows.
    #ifdef LIB_SHARED
        #ifdef LIB_EXPORTS
            #define LIB_API __declspec(dllexport)
        #else
            #define LIB_API __declspec(dllimport)
        #endif
    #else
        // Disable definition if linking statically.
        #define LIB_API
    #endif
#else
    // Disable definition for non-Win32 systems.
    #define LIB_API
#endif

#include <string>
#include <utility>
namespace opendlv { namespace proxy {
using namespace std::string_literals; // NOLINT
class LIB_API GroundSteeringReading {
    public:
        GroundSteeringReading() = default;
        GroundSteeringReading(const GroundSteeringReading&) = default;
        GroundSteeringReading& operator=(const GroundSteeringReading&) = default;
        GroundSteeringReading(GroundSteeringReading&&) noexcept = default; // NOLINT
        GroundSteeringReading& operator=(GroundSteeringReading&&) noexcept = default; // NOLINT
        ~GroundSteeringReading() = default;

    public:
        static uint32_t ID();
        static const std::string ShortName();
        static const std::string LongName();
        
        GroundSteeringReading& steeringAngle(const float &v) noexcept;
        float steeringAngle() const noexcept;
        

        template<class Visitor>
        void accept(Visitor &visitor) {
            visitor.preVisit(ID(), ShortName(), LongName());
            
            doVisit(1, std::move("float"s), std::move("steeringAngle"s), m_steeringAngle, visitor);
            
            visitor.postVisit();
        }

        template<class PreVisitor, class Visitor, class PostVisitor>
        void accept(PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
            std::forward<PreVisitor>(preVisit)(ID(), ShortName(), LongName());
            
            doTripletForwardVisit(1, std::move("float"s), std::move("steeringAngle"s), m_steeringAngle, preVisit, visit, postVisit);
            
            std::forward<PostVisitor>(postVisit)();
        }

    private:
        
        float m_steeringAngle{ 0.0f }; // field identifier = 1.
        
};
}}

template<>
struct isVisitable<opendlv::proxy::GroundSteeringReading> {
    static const bool value = true;
};
template<>
struct isTripletForwardVisitable<opendlv::proxy::GroundSteeringReading> {
    static const bool value = true;
};
#endif


/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef VISITABLE_TYPE_TRAIT
#define VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct visitorSelector {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct visitorSelector<true> {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<typename T>
struct isVisitable {
    static const bool value = false;
};

template<typename T, class Visitor>
void doVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
    visitorSelector<isVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, visitor);
}
#endif

#ifndef TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#define TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct tripletForwardVisitorSelector {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)preVisit;
        (void)postVisit;
        std::forward<Visitor>(visit)(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct tripletForwardVisitorSelector<true> {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)fieldIdentifier;
        (void)typeName;
        (void)name;
        // Apply preVisit, visit, and postVisit on value.
        value.accept(preVisit, visit, postVisit);
    }
};

template<typename T>
struct isTripletForwardVisitable {
    static const bool value = false;
};

template< typename T, class PreVisitor, class Visitor, class PostVisitor>
void doTripletForwardVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
    tripletForwardVisitorSelector<isTripletForwardVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, std::move(preVisit), std::move(visit), std::move(postVisit)); // NOLINT
}
#endif


#ifndef OPENDLV_PROXY_PEDALPOSITIONREADING_HPP
#define OPENDLV_PROXY_PEDALPOSITIONREADING_HPP

#ifdef WIN32
    // Export symbols if compile flags "LIB_SHARED" and "LIB_EXPORTS" are set on Windows.
    #ifdef LIB_SHARED
        #ifdef LIB_EXPORTS
            #define LIB_API __declspec(dllexport)
        #else
            #define LIB_API __declspec(dllimport)
        #endif
    #else
        // Disable definition if linking statically.
        #define LIB_API
    #endif
#else
    // Disable definition for non-Win32 systems.
    #define LIB_API
#endif

#include <string>
#include <utility>
namespace opendlv { namespace proxy {
using namespace std::string_literals; // NOLINT
class LIB_API PedalPositionReading {
    public:
        PedalPositionReading() = default;
        PedalPositionReading(const PedalPositionReading&) = default;
        PedalPositionReading& operator=(const PedalPositionReading&) = default;
        PedalPositionReading(PedalPositionReading&&) noexcept = default; // NOLINT
        PedalPositionReading& operator=(PedalPositionReading&&) noexcept = default; // NOLINT
        ~PedalPositionReading() = default;

    public:
        static uint32_t ID();
        static const std::string ShortName();
        static const std::string LongName();
        
        PedalPositionReading& percent(const float &v) noexcept;
        float percent() const noexcept;
        

        template<class Visitor>
        void accept(Visitor &visitor) {
            visitor.preVisit(ID(), ShortName(), LongName());
            
            doVisit(1, std::move("float"s), std::move("percent"s), m_percent, visitor);
            
            visitor.postVisit();
        }

        template<class PreVisitor, class Visitor, class PostVisitor>
        void accept(PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
            std::forward<PreVisitor>(preVisit)(ID(), ShortName(), LongName());
            
            doTripletForwardVisit(1, std::move("float"s), std::move("percent"s), m_percent, preVisit, visit, postVisit);
            
            std::forward<PostVisitor>(postVisit)();
        }

    private:
        
        float m_percent{ 0.0f }; // field identifier = 1.
        
};
}}

template<>
struct isVisitable<opendlv::proxy::PedalPositionReading> {
    static const bool value = true;
};
template<>
struct isTripletForwardVisitable<opendlv::proxy::PedalPositionReading> {
    static const bool value = true;
};
#endif


/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef VISITABLE_TYPE_TRAIT
#define VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct visitorSelector {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct visitorSelector<true> {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<typename T>
struct isVisitable {
    static const bool value = false;
};

template<typename T, class Visitor>
void doVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
    visitorSelector<isVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, visitor);
}
#endif

#ifndef TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#define TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct tripletForwardVisitorSelector {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)preVisit;
        (void)postVisit;
        std::forward<Visitor>(visit)(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct tripletForwardVisitorSelector<true> {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)fieldIdentifier;
        (void)typeName;
        (void)name;
        // Apply preVisit, visit, and postVisit on value.
        value.accept(preVisit, visit, postVisit);
    }
};

template<typename T>
struct isTripletForwardVisitable {
    static const bool value = false;
};

template< typename T, class PreVisitor, class Visitor, class PostVisitor>
void doTripletForwardVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
    tripletForwardVisitorSelector<isTripletForwardVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, std::move(preVisit), std::move(visit), std::move(postVisit)); // NOLINT
}
#endif


#ifndef VEHICLECONTROL_HPP
#define VEHICLECONTROL_HPP

#ifdef WIN32
    // Export symbols if compile flags "LIB_SHARED" and "LIB_EXPORTS" are set on Windows.
    #ifdef LIB_SHARED
        #ifdef LIB_EXPORTS
            #define LIB_API __declspec(dllexport)
        #else
            #define LIB_API __declspec(dllimport)
        #endif
    #else
        // Disable definition if linking statically.
        #define LIB_API
    #endif
#else
    // Disable definition for non-Win32 systems.
    #define LIB_API
#endif

#include <string>
#include <utility>

using namespace std::string_literals; // NOLINT
class LIB_API VehicleControl {
    public:
        VehicleControl() = default;
        VehicleControl(const VehicleControl&) = default;
        VehicleControl& operator=(const VehicleControl&) = default;
        VehicleControl(VehicleControl&&) noexcept = default; // NOLINT
        VehicleControl& operator=(VehicleControl&&) noexcept = default; // NOLINT
        ~VehicleControl() = default;

    public:
        static uint32_t ID();
        static const std::string ShortName();
        static const std::string LongName();
        
        VehicleControl& pedalPosition(const float &v) noexcept;
        float pedalPosition() const noexcept;
        
        VehicleControl& steeringAngle(const float &v) noexcept;
        float steeringAngle() const noexcept;
        
        VehicleControl& odometerData(const int &v) noexcept;
        int odometerData() const noexcept;
        

        template<class Visitor>
        void accept(Visitor &visitor) {
            visitor.preVisit(ID(), ShortName(), LongName());
            
            doVisit(1, std::move("float"s), std::move("pedalPosition"s), m_pedalPosition, visitor);
            
            doVisit(2, std::move("float"s), std::move("steeringAngle"s), m_steeringAngle, visitor);
            
            doVisit(3, std::move("int"s), std::move("odometerData"s), m_odometerData, visitor);
            
            visitor.postVisit();
        }

        template<class PreVisitor, class Visitor, class PostVisitor>
        void accept(PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
            std::forward<PreVisitor>(preVisit)(ID(), ShortName(), LongName());
            
            doTripletForwardVisit(1, std::move("float"s), std::move("pedalPosition"s), m_pedalPosition, preVisit, visit, postVisit);
            
            doTripletForwardVisit(2, std::move("float"s), std::move("steeringAngle"s), m_steeringAngle, preVisit, visit, postVisit);
            
            doTripletForwardVisit(3, std::move("int"s), std::move("odometerData"s), m_odometerData, preVisit, visit, postVisit);
            
            std::forward<PostVisitor>(postVisit)();
        }

    private:
        
        float m_pedalPosition{ 0.0f }; // field identifier = 1.
        
        float m_steeringAngle{ 0.0f }; // field identifier = 2.
        
        int m_odometerData{  }; // field identifier = 3.
        
};


template<>
struct isVisitable<VehicleControl> {
    static const bool value = true;
};
template<>
struct isTripletForwardVisitable<VehicleControl> {
    static const bool value = true;
};
#endif

