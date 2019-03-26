// Auto-generated. Do not edit!

// (in-package gruppe3.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class signal_robot {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.abratio = null;
      this.detectcolor = null;
      this.detect_done = null;
      this.reportgoal = null;
      this.odometrie_1 = null;
      this.odometrie_2 = null;
    }
    else {
      if (initObj.hasOwnProperty('abratio')) {
        this.abratio = initObj.abratio
      }
      else {
        this.abratio = 0.0;
      }
      if (initObj.hasOwnProperty('detectcolor')) {
        this.detectcolor = initObj.detectcolor
      }
      else {
        this.detectcolor = 0;
      }
      if (initObj.hasOwnProperty('detect_done')) {
        this.detect_done = initObj.detect_done
      }
      else {
        this.detect_done = false;
      }
      if (initObj.hasOwnProperty('reportgoal')) {
        this.reportgoal = initObj.reportgoal
      }
      else {
        this.reportgoal = 0;
      }
      if (initObj.hasOwnProperty('odometrie_1')) {
        this.odometrie_1 = initObj.odometrie_1
      }
      else {
        this.odometrie_1 = new geometry_msgs.msg.Pose2D();
      }
      if (initObj.hasOwnProperty('odometrie_2')) {
        this.odometrie_2 = initObj.odometrie_2
      }
      else {
        this.odometrie_2 = new geometry_msgs.msg.Pose2D();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type signal_robot
    // Serialize message field [abratio]
    bufferOffset = _serializer.float64(obj.abratio, buffer, bufferOffset);
    // Serialize message field [detectcolor]
    bufferOffset = _serializer.int8(obj.detectcolor, buffer, bufferOffset);
    // Serialize message field [detect_done]
    bufferOffset = _serializer.bool(obj.detect_done, buffer, bufferOffset);
    // Serialize message field [reportgoal]
    bufferOffset = _serializer.int8(obj.reportgoal, buffer, bufferOffset);
    // Serialize message field [odometrie_1]
    bufferOffset = geometry_msgs.msg.Pose2D.serialize(obj.odometrie_1, buffer, bufferOffset);
    // Serialize message field [odometrie_2]
    bufferOffset = geometry_msgs.msg.Pose2D.serialize(obj.odometrie_2, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type signal_robot
    let len;
    let data = new signal_robot(null);
    // Deserialize message field [abratio]
    data.abratio = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [detectcolor]
    data.detectcolor = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [detect_done]
    data.detect_done = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [reportgoal]
    data.reportgoal = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [odometrie_1]
    data.odometrie_1 = geometry_msgs.msg.Pose2D.deserialize(buffer, bufferOffset);
    // Deserialize message field [odometrie_2]
    data.odometrie_2 = geometry_msgs.msg.Pose2D.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 59;
  }

  static datatype() {
    // Returns string type for a message object
    return 'gruppe3/signal_robot';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7edb32daa132df4f0725a8b5753c4c95';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64               abratio      
    int8                  detectcolor  
    bool                  detect_done 
    int8                  reportgoal
    geometry_msgs/Pose2D   odometrie_1 
    geometry_msgs/Pose2D   odometrie_2
    
    ================================================================================
    MSG: geometry_msgs/Pose2D
    # Deprecated
    # Please use the full 3D pose.
    
    # In general our recommendation is to use a full 3D representation of everything and for 2D specific applications make the appropriate projections into the plane for their calculations but optimally will preserve the 3D information during processing.
    
    # If we have parallel copies of 2D datatypes every UI and other pipeline will end up needing to have dual interfaces to plot everything. And you will end up with not being able to use 3D tools for 2D use cases even if they're completely valid, as you'd have to reimplement it with different inputs and outputs. It's not particularly hard to plot the 2D pose or compute the yaw error for the Pose message and there are already tools and libraries that can do this for you.
    
    
    # This expresses a position and orientation on a 2D manifold.
    
    float64 x
    float64 y
    float64 theta
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new signal_robot(null);
    if (msg.abratio !== undefined) {
      resolved.abratio = msg.abratio;
    }
    else {
      resolved.abratio = 0.0
    }

    if (msg.detectcolor !== undefined) {
      resolved.detectcolor = msg.detectcolor;
    }
    else {
      resolved.detectcolor = 0
    }

    if (msg.detect_done !== undefined) {
      resolved.detect_done = msg.detect_done;
    }
    else {
      resolved.detect_done = false
    }

    if (msg.reportgoal !== undefined) {
      resolved.reportgoal = msg.reportgoal;
    }
    else {
      resolved.reportgoal = 0
    }

    if (msg.odometrie_1 !== undefined) {
      resolved.odometrie_1 = geometry_msgs.msg.Pose2D.Resolve(msg.odometrie_1)
    }
    else {
      resolved.odometrie_1 = new geometry_msgs.msg.Pose2D()
    }

    if (msg.odometrie_2 !== undefined) {
      resolved.odometrie_2 = geometry_msgs.msg.Pose2D.Resolve(msg.odometrie_2)
    }
    else {
      resolved.odometrie_2 = new geometry_msgs.msg.Pose2D()
    }

    return resolved;
    }
};

module.exports = signal_robot;
