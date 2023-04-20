// Auto-generated. Do not edit!

// (in-package plumbing_server_client.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class AddintsRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.num1 = null;
      this.num2 = null;
    }
    else {
      if (initObj.hasOwnProperty('num1')) {
        this.num1 = initObj.num1
      }
      else {
        this.num1 = 0;
      }
      if (initObj.hasOwnProperty('num2')) {
        this.num2 = initObj.num2
      }
      else {
        this.num2 = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type AddintsRequest
    // Serialize message field [num1]
    bufferOffset = _serializer.int32(obj.num1, buffer, bufferOffset);
    // Serialize message field [num2]
    bufferOffset = _serializer.int32(obj.num2, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type AddintsRequest
    let len;
    let data = new AddintsRequest(null);
    // Deserialize message field [num1]
    data.num1 = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [num2]
    data.num2 = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'plumbing_server_client/AddintsRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c68f3979e1a90aac7d1c75a1096d1e60';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # 自定义服务消息的载体
    int32 num1
    int32 num2
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new AddintsRequest(null);
    if (msg.num1 !== undefined) {
      resolved.num1 = msg.num1;
    }
    else {
      resolved.num1 = 0
    }

    if (msg.num2 !== undefined) {
      resolved.num2 = msg.num2;
    }
    else {
      resolved.num2 = 0
    }

    return resolved;
    }
};

class AddintsResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.sum = null;
    }
    else {
      if (initObj.hasOwnProperty('sum')) {
        this.sum = initObj.sum
      }
      else {
        this.sum = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type AddintsResponse
    // Serialize message field [sum]
    bufferOffset = _serializer.int32(obj.sum, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type AddintsResponse
    let len;
    let data = new AddintsResponse(null);
    // Deserialize message field [sum]
    data.sum = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'plumbing_server_client/AddintsResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '0ba699c25c9418c0366f3595c0c8e8ec';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 sum
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new AddintsResponse(null);
    if (msg.sum !== undefined) {
      resolved.sum = msg.sum;
    }
    else {
      resolved.sum = 0
    }

    return resolved;
    }
};

module.exports = {
  Request: AddintsRequest,
  Response: AddintsResponse,
  md5sum() { return '4781436a0c2affec8025955a6041e481'; },
  datatype() { return 'plumbing_server_client/Addints'; }
};
