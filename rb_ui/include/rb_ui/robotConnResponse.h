// Generated by gencpp from file rb_ui/robotConnResponse.msg
// DO NOT EDIT!


#ifndef RB_UI_MESSAGE_ROBOTCONNRESPONSE_H
#define RB_UI_MESSAGE_ROBOTCONNRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace rb_ui
{
template <class ContainerAllocator>
struct robotConnResponse_
{
  typedef robotConnResponse_<ContainerAllocator> Type;

  robotConnResponse_()
    : ret(false)  {
    }
  robotConnResponse_(const ContainerAllocator& _alloc)
    : ret(false)  {
  (void)_alloc;
    }



   typedef uint8_t _ret_type;
  _ret_type ret;





  typedef boost::shared_ptr< ::rb_ui::robotConnResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::rb_ui::robotConnResponse_<ContainerAllocator> const> ConstPtr;

}; // struct robotConnResponse_

typedef ::rb_ui::robotConnResponse_<std::allocator<void> > robotConnResponse;

typedef boost::shared_ptr< ::rb_ui::robotConnResponse > robotConnResponsePtr;
typedef boost::shared_ptr< ::rb_ui::robotConnResponse const> robotConnResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::rb_ui::robotConnResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::rb_ui::robotConnResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace rb_ui

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::rb_ui::robotConnResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::rb_ui::robotConnResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::rb_ui::robotConnResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::rb_ui::robotConnResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::rb_ui::robotConnResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::rb_ui::robotConnResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::rb_ui::robotConnResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e2cc9e9d8c464550830df49c160979ad";
  }

  static const char* value(const ::rb_ui::robotConnResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe2cc9e9d8c464550ULL;
  static const uint64_t static_value2 = 0x830df49c160979adULL;
};

template<class ContainerAllocator>
struct DataType< ::rb_ui::robotConnResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "rb_ui/robotConnResponse";
  }

  static const char* value(const ::rb_ui::robotConnResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::rb_ui::robotConnResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool ret\n\
\n\
";
  }

  static const char* value(const ::rb_ui::robotConnResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::rb_ui::robotConnResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.ret);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct robotConnResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::rb_ui::robotConnResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::rb_ui::robotConnResponse_<ContainerAllocator>& v)
  {
    s << indent << "ret: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.ret);
  }
};

} // namespace message_operations
} // namespace ros

#endif // RB_UI_MESSAGE_ROBOTCONNRESPONSE_H
