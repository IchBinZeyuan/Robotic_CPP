// Generated by gencpp from file gruppe3/signal_robot.msg
// DO NOT EDIT!


#ifndef GRUPPE3_MESSAGE_SIGNAL_ROBOT_H
#define GRUPPE3_MESSAGE_SIGNAL_ROBOT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/Pose2D.h>
#include <geometry_msgs/Pose2D.h>

namespace gruppe3
{
template <class ContainerAllocator>
struct signal_robot_
{
  typedef signal_robot_<ContainerAllocator> Type;

  signal_robot_()
    : abratio(0.0)
    , detectcolor(0)
    , detect_done(false)
    , reportgoal(0)
    , odometrie_1()
    , odometrie_2()  {
    }
  signal_robot_(const ContainerAllocator& _alloc)
    : abratio(0.0)
    , detectcolor(0)
    , detect_done(false)
    , reportgoal(0)
    , odometrie_1(_alloc)
    , odometrie_2(_alloc)  {
  (void)_alloc;
    }



   typedef double _abratio_type;
  _abratio_type abratio;

   typedef int8_t _detectcolor_type;
  _detectcolor_type detectcolor;

   typedef uint8_t _detect_done_type;
  _detect_done_type detect_done;

   typedef int8_t _reportgoal_type;
  _reportgoal_type reportgoal;

   typedef  ::geometry_msgs::Pose2D_<ContainerAllocator>  _odometrie_1_type;
  _odometrie_1_type odometrie_1;

   typedef  ::geometry_msgs::Pose2D_<ContainerAllocator>  _odometrie_2_type;
  _odometrie_2_type odometrie_2;





  typedef boost::shared_ptr< ::gruppe3::signal_robot_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::gruppe3::signal_robot_<ContainerAllocator> const> ConstPtr;

}; // struct signal_robot_

typedef ::gruppe3::signal_robot_<std::allocator<void> > signal_robot;

typedef boost::shared_ptr< ::gruppe3::signal_robot > signal_robotPtr;
typedef boost::shared_ptr< ::gruppe3::signal_robot const> signal_robotConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::gruppe3::signal_robot_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::gruppe3::signal_robot_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace gruppe3

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'gruppe3': ['/home/ge34caj/catkin_ws_test/src/gruppe3/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::gruppe3::signal_robot_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::gruppe3::signal_robot_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::gruppe3::signal_robot_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::gruppe3::signal_robot_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::gruppe3::signal_robot_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::gruppe3::signal_robot_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::gruppe3::signal_robot_<ContainerAllocator> >
{
  static const char* value()
  {
    return "7edb32daa132df4f0725a8b5753c4c95";
  }

  static const char* value(const ::gruppe3::signal_robot_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x7edb32daa132df4fULL;
  static const uint64_t static_value2 = 0x0725a8b5753c4c95ULL;
};

template<class ContainerAllocator>
struct DataType< ::gruppe3::signal_robot_<ContainerAllocator> >
{
  static const char* value()
  {
    return "gruppe3/signal_robot";
  }

  static const char* value(const ::gruppe3::signal_robot_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::gruppe3::signal_robot_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64               abratio      \n\
int8                  detectcolor  \n\
bool                  detect_done \n\
int8                  reportgoal\n\
geometry_msgs/Pose2D   odometrie_1 \n\
geometry_msgs/Pose2D   odometrie_2\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Pose2D\n\
# Deprecated\n\
# Please use the full 3D pose.\n\
\n\
# In general our recommendation is to use a full 3D representation of everything and for 2D specific applications make the appropriate projections into the plane for their calculations but optimally will preserve the 3D information during processing.\n\
\n\
# If we have parallel copies of 2D datatypes every UI and other pipeline will end up needing to have dual interfaces to plot everything. And you will end up with not being able to use 3D tools for 2D use cases even if they're completely valid, as you'd have to reimplement it with different inputs and outputs. It's not particularly hard to plot the 2D pose or compute the yaw error for the Pose message and there are already tools and libraries that can do this for you.\n\
\n\
\n\
# This expresses a position and orientation on a 2D manifold.\n\
\n\
float64 x\n\
float64 y\n\
float64 theta\n\
";
  }

  static const char* value(const ::gruppe3::signal_robot_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::gruppe3::signal_robot_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.abratio);
      stream.next(m.detectcolor);
      stream.next(m.detect_done);
      stream.next(m.reportgoal);
      stream.next(m.odometrie_1);
      stream.next(m.odometrie_2);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct signal_robot_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::gruppe3::signal_robot_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::gruppe3::signal_robot_<ContainerAllocator>& v)
  {
    s << indent << "abratio: ";
    Printer<double>::stream(s, indent + "  ", v.abratio);
    s << indent << "detectcolor: ";
    Printer<int8_t>::stream(s, indent + "  ", v.detectcolor);
    s << indent << "detect_done: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.detect_done);
    s << indent << "reportgoal: ";
    Printer<int8_t>::stream(s, indent + "  ", v.reportgoal);
    s << indent << "odometrie_1: ";
    s << std::endl;
    Printer< ::geometry_msgs::Pose2D_<ContainerAllocator> >::stream(s, indent + "  ", v.odometrie_1);
    s << indent << "odometrie_2: ";
    s << std::endl;
    Printer< ::geometry_msgs::Pose2D_<ContainerAllocator> >::stream(s, indent + "  ", v.odometrie_2);
  }
};

} // namespace message_operations
} // namespace ros

#endif // GRUPPE3_MESSAGE_SIGNAL_ROBOT_H
