; Auto-generated. Do not edit!


(cl:in-package robottest-msg)


;//! \htmlinclude signal_transfer.msg.html

(cl:defclass <signal_transfer> (roslisp-msg-protocol:ros-message)
  ((detectionstart
    :reader detectionstart
    :initarg :detectionstart
    :type cl:boolean
    :initform cl:nil)
   (gamestart
    :reader gamestart
    :initarg :gamestart
    :type cl:boolean
    :initform cl:nil)
   (stop
    :reader stop
    :initarg :stop
    :type cl:boolean
    :initform cl:nil)
   (true_a
    :reader true_a
    :initarg :true_a
    :type cl:float
    :initform 0.0)
   (true_b
    :reader true_b
    :initarg :true_b
    :type cl:float
    :initform 0.0)
   (T_color
    :reader T_color
    :initarg :T_color
    :type cl:fixnum
    :initform 0))
)

(cl:defclass signal_transfer (<signal_transfer>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <signal_transfer>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'signal_transfer)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robottest-msg:<signal_transfer> is deprecated: use robottest-msg:signal_transfer instead.")))

(cl:ensure-generic-function 'detectionstart-val :lambda-list '(m))
(cl:defmethod detectionstart-val ((m <signal_transfer>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robottest-msg:detectionstart-val is deprecated.  Use robottest-msg:detectionstart instead.")
  (detectionstart m))

(cl:ensure-generic-function 'gamestart-val :lambda-list '(m))
(cl:defmethod gamestart-val ((m <signal_transfer>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robottest-msg:gamestart-val is deprecated.  Use robottest-msg:gamestart instead.")
  (gamestart m))

(cl:ensure-generic-function 'stop-val :lambda-list '(m))
(cl:defmethod stop-val ((m <signal_transfer>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robottest-msg:stop-val is deprecated.  Use robottest-msg:stop instead.")
  (stop m))

(cl:ensure-generic-function 'true_a-val :lambda-list '(m))
(cl:defmethod true_a-val ((m <signal_transfer>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robottest-msg:true_a-val is deprecated.  Use robottest-msg:true_a instead.")
  (true_a m))

(cl:ensure-generic-function 'true_b-val :lambda-list '(m))
(cl:defmethod true_b-val ((m <signal_transfer>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robottest-msg:true_b-val is deprecated.  Use robottest-msg:true_b instead.")
  (true_b m))

(cl:ensure-generic-function 'T_color-val :lambda-list '(m))
(cl:defmethod T_color-val ((m <signal_transfer>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robottest-msg:T_color-val is deprecated.  Use robottest-msg:T_color instead.")
  (T_color m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <signal_transfer>) ostream)
  "Serializes a message object of type '<signal_transfer>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'detectionstart) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'gamestart) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'stop) 1 0)) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'true_a))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'true_b))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'T_color)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <signal_transfer>) istream)
  "Deserializes a message object of type '<signal_transfer>"
    (cl:setf (cl:slot-value msg 'detectionstart) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'gamestart) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'stop) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'true_a) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'true_b) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'T_color) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<signal_transfer>)))
  "Returns string type for a message object of type '<signal_transfer>"
  "robottest/signal_transfer")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'signal_transfer)))
  "Returns string type for a message object of type 'signal_transfer"
  "robottest/signal_transfer")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<signal_transfer>)))
  "Returns md5sum for a message object of type '<signal_transfer>"
  "1b8d9240a4bf9c05c0ffc88fd32a8535")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'signal_transfer)))
  "Returns md5sum for a message object of type 'signal_transfer"
  "1b8d9240a4bf9c05c0ffc88fd32a8535")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<signal_transfer>)))
  "Returns full string definition for message of type '<signal_transfer>"
  (cl:format cl:nil " ~%bool  detectionstart        # bool detect_start signal~%bool  gamestart             # bool game_start signal~%bool  stop                  # bool stop_signal~%float64 true_a              # float default_a~%float64 true_b              # float default_b~%int8  T_color               # int8 default_color 0 yellow, 1 blue~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'signal_transfer)))
  "Returns full string definition for message of type 'signal_transfer"
  (cl:format cl:nil " ~%bool  detectionstart        # bool detect_start signal~%bool  gamestart             # bool game_start signal~%bool  stop                  # bool stop_signal~%float64 true_a              # float default_a~%float64 true_b              # float default_b~%int8  T_color               # int8 default_color 0 yellow, 1 blue~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <signal_transfer>))
  (cl:+ 0
     1
     1
     1
     8
     8
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <signal_transfer>))
  "Converts a ROS message object to a list"
  (cl:list 'signal_transfer
    (cl:cons ':detectionstart (detectionstart msg))
    (cl:cons ':gamestart (gamestart msg))
    (cl:cons ':stop (stop msg))
    (cl:cons ':true_a (true_a msg))
    (cl:cons ':true_b (true_b msg))
    (cl:cons ':T_color (T_color msg))
))
