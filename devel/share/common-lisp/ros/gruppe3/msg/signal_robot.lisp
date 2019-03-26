; Auto-generated. Do not edit!


(cl:in-package gruppe3-msg)


;//! \htmlinclude signal_robot.msg.html

(cl:defclass <signal_robot> (roslisp-msg-protocol:ros-message)
  ((abratio
    :reader abratio
    :initarg :abratio
    :type cl:float
    :initform 0.0)
   (detectcolor
    :reader detectcolor
    :initarg :detectcolor
    :type cl:fixnum
    :initform 0)
   (detect_done
    :reader detect_done
    :initarg :detect_done
    :type cl:boolean
    :initform cl:nil)
   (reportgoal
    :reader reportgoal
    :initarg :reportgoal
    :type cl:fixnum
    :initform 0)
   (odometrie_1
    :reader odometrie_1
    :initarg :odometrie_1
    :type geometry_msgs-msg:Pose2D
    :initform (cl:make-instance 'geometry_msgs-msg:Pose2D))
   (odometrie_2
    :reader odometrie_2
    :initarg :odometrie_2
    :type geometry_msgs-msg:Pose2D
    :initform (cl:make-instance 'geometry_msgs-msg:Pose2D)))
)

(cl:defclass signal_robot (<signal_robot>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <signal_robot>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'signal_robot)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name gruppe3-msg:<signal_robot> is deprecated: use gruppe3-msg:signal_robot instead.")))

(cl:ensure-generic-function 'abratio-val :lambda-list '(m))
(cl:defmethod abratio-val ((m <signal_robot>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gruppe3-msg:abratio-val is deprecated.  Use gruppe3-msg:abratio instead.")
  (abratio m))

(cl:ensure-generic-function 'detectcolor-val :lambda-list '(m))
(cl:defmethod detectcolor-val ((m <signal_robot>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gruppe3-msg:detectcolor-val is deprecated.  Use gruppe3-msg:detectcolor instead.")
  (detectcolor m))

(cl:ensure-generic-function 'detect_done-val :lambda-list '(m))
(cl:defmethod detect_done-val ((m <signal_robot>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gruppe3-msg:detect_done-val is deprecated.  Use gruppe3-msg:detect_done instead.")
  (detect_done m))

(cl:ensure-generic-function 'reportgoal-val :lambda-list '(m))
(cl:defmethod reportgoal-val ((m <signal_robot>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gruppe3-msg:reportgoal-val is deprecated.  Use gruppe3-msg:reportgoal instead.")
  (reportgoal m))

(cl:ensure-generic-function 'odometrie_1-val :lambda-list '(m))
(cl:defmethod odometrie_1-val ((m <signal_robot>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gruppe3-msg:odometrie_1-val is deprecated.  Use gruppe3-msg:odometrie_1 instead.")
  (odometrie_1 m))

(cl:ensure-generic-function 'odometrie_2-val :lambda-list '(m))
(cl:defmethod odometrie_2-val ((m <signal_robot>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gruppe3-msg:odometrie_2-val is deprecated.  Use gruppe3-msg:odometrie_2 instead.")
  (odometrie_2 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <signal_robot>) ostream)
  "Serializes a message object of type '<signal_robot>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'abratio))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'detectcolor)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'detect_done) 1 0)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'reportgoal)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'odometrie_1) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'odometrie_2) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <signal_robot>) istream)
  "Deserializes a message object of type '<signal_robot>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'abratio) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'detectcolor) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:setf (cl:slot-value msg 'detect_done) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'reportgoal) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'odometrie_1) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'odometrie_2) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<signal_robot>)))
  "Returns string type for a message object of type '<signal_robot>"
  "gruppe3/signal_robot")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'signal_robot)))
  "Returns string type for a message object of type 'signal_robot"
  "gruppe3/signal_robot")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<signal_robot>)))
  "Returns md5sum for a message object of type '<signal_robot>"
  "7edb32daa132df4f0725a8b5753c4c95")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'signal_robot)))
  "Returns md5sum for a message object of type 'signal_robot"
  "7edb32daa132df4f0725a8b5753c4c95")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<signal_robot>)))
  "Returns full string definition for message of type '<signal_robot>"
  (cl:format cl:nil "float64               abratio      ~%int8                  detectcolor  ~%bool                  detect_done ~%int8                  reportgoal~%geometry_msgs/Pose2D   odometrie_1 ~%geometry_msgs/Pose2D   odometrie_2~%~%================================================================================~%MSG: geometry_msgs/Pose2D~%# Deprecated~%# Please use the full 3D pose.~%~%# In general our recommendation is to use a full 3D representation of everything and for 2D specific applications make the appropriate projections into the plane for their calculations but optimally will preserve the 3D information during processing.~%~%# If we have parallel copies of 2D datatypes every UI and other pipeline will end up needing to have dual interfaces to plot everything. And you will end up with not being able to use 3D tools for 2D use cases even if they're completely valid, as you'd have to reimplement it with different inputs and outputs. It's not particularly hard to plot the 2D pose or compute the yaw error for the Pose message and there are already tools and libraries that can do this for you.~%~%~%# This expresses a position and orientation on a 2D manifold.~%~%float64 x~%float64 y~%float64 theta~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'signal_robot)))
  "Returns full string definition for message of type 'signal_robot"
  (cl:format cl:nil "float64               abratio      ~%int8                  detectcolor  ~%bool                  detect_done ~%int8                  reportgoal~%geometry_msgs/Pose2D   odometrie_1 ~%geometry_msgs/Pose2D   odometrie_2~%~%================================================================================~%MSG: geometry_msgs/Pose2D~%# Deprecated~%# Please use the full 3D pose.~%~%# In general our recommendation is to use a full 3D representation of everything and for 2D specific applications make the appropriate projections into the plane for their calculations but optimally will preserve the 3D information during processing.~%~%# If we have parallel copies of 2D datatypes every UI and other pipeline will end up needing to have dual interfaces to plot everything. And you will end up with not being able to use 3D tools for 2D use cases even if they're completely valid, as you'd have to reimplement it with different inputs and outputs. It's not particularly hard to plot the 2D pose or compute the yaw error for the Pose message and there are already tools and libraries that can do this for you.~%~%~%# This expresses a position and orientation on a 2D manifold.~%~%float64 x~%float64 y~%float64 theta~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <signal_robot>))
  (cl:+ 0
     8
     1
     1
     1
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'odometrie_1))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'odometrie_2))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <signal_robot>))
  "Converts a ROS message object to a list"
  (cl:list 'signal_robot
    (cl:cons ':abratio (abratio msg))
    (cl:cons ':detectcolor (detectcolor msg))
    (cl:cons ':detect_done (detect_done msg))
    (cl:cons ':reportgoal (reportgoal msg))
    (cl:cons ':odometrie_1 (odometrie_1 msg))
    (cl:cons ':odometrie_2 (odometrie_2 msg))
))
