// Auto-generated. Do not edit!

// (in-package gruppe3.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class signal_transfer {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.detectionstart = null;
      this.gamestart = null;
      this.stop = null;
      this.true_a = null;
      this.true_b = null;
      this.T_color = null;
    }
    else {
      if (initObj.hasOwnProperty('detectionstart')) {
        this.detectionstart = initObj.detectionstart
      }
      else {
        this.detectionstart = false;
      }
      if (initObj.hasOwnProperty('gamestart')) {
        this.gamestart = initObj.gamestart
      }
      else {
        this.gamestart = false;
      }
      if (initObj.hasOwnProperty('stop')) {
        this.stop = initObj.stop
      }
      else {
        this.stop = false;
      }
      if (initObj.hasOwnProperty('true_a')) {
        this.true_a = initObj.true_a
      }
      else {
        this.true_a = 0.0;
      }
      if (initObj.hasOwnProperty('true_b')) {
        this.true_b = initObj.true_b
      }
      else {
        this.true_b = 0.0;
      }
      if (initObj.hasOwnProperty('T_color')) {
        this.T_color = initObj.T_color
      }
      else {
        this.T_color = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type signal_transfer
    // Serialize message field [detectionstart]
    bufferOffset = _serializer.bool(obj.detectionstart, buffer, bufferOffset);
    // Serialize message field [gamestart]
    bufferOffset = _serializer.bool(obj.gamestart, buffer, bufferOffset);
    // Serialize message field [stop]
    bufferOffset = _serializer.bool(obj.stop, buffer, bufferOffset);
    // Serialize message field [true_a]
    bufferOffset = _serializer.float64(obj.true_a, buffer, bufferOffset);
    // Serialize message field [true_b]
    bufferOffset = _serializer.float64(obj.true_b, buffer, bufferOffset);
    // Serialize message field [T_color]
    bufferOffset = _serializer.int8(obj.T_color, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type signal_transfer
    let len;
    let data = new signal_transfer(null);
    // Deserialize message field [detectionstart]
    data.detectionstart = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [gamestart]
    data.gamestart = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [stop]
    data.stop = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [true_a]
    data.true_a = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [true_b]
    data.true_b = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [T_color]
    data.T_color = _deserializer.int8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 20;
  }

  static datatype() {
    // Returns string type for a message object
    return 'gruppe3/signal_transfer';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1b8d9240a4bf9c05c0ffc88fd32a8535';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
     
    bool  detectionstart        # bool detect_start signal
    bool  gamestart             # bool game_start signal
    bool  stop                  # bool stop_signal
    float64 true_a              # float default_a
    float64 true_b              # float default_b
    int8  T_color               # int8 default_color 0 yellow, 1 blue
    
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new signal_transfer(null);
    if (msg.detectionstart !== undefined) {
      resolved.detectionstart = msg.detectionstart;
    }
    else {
      resolved.detectionstart = false
    }

    if (msg.gamestart !== undefined) {
      resolved.gamestart = msg.gamestart;
    }
    else {
      resolved.gamestart = false
    }

    if (msg.stop !== undefined) {
      resolved.stop = msg.stop;
    }
    else {
      resolved.stop = false
    }

    if (msg.true_a !== undefined) {
      resolved.true_a = msg.true_a;
    }
    else {
      resolved.true_a = 0.0
    }

    if (msg.true_b !== undefined) {
      resolved.true_b = msg.true_b;
    }
    else {
      resolved.true_b = 0.0
    }

    if (msg.T_color !== undefined) {
      resolved.T_color = msg.T_color;
    }
    else {
      resolved.T_color = 0
    }

    return resolved;
    }
};

module.exports = signal_transfer;
