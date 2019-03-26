;; Auto-generated. Do not edit!


(when (boundp 'robottest::signal_robot)
  (if (not (find-package "ROBOTTEST"))
    (make-package "ROBOTTEST"))
  (shadow 'signal_robot (find-package "ROBOTTEST")))
(unless (find-package "ROBOTTEST::SIGNAL_ROBOT")
  (make-package "ROBOTTEST::SIGNAL_ROBOT"))

(in-package "ROS")
;;//! \htmlinclude signal_robot.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass robottest::signal_robot
  :super ros::object
  :slots (_abratio _detectcolor _detect_done _reportgoal _odometrie_1 _odometrie_2 ))

(defmethod robottest::signal_robot
  (:init
   (&key
    ((:abratio __abratio) 0.0)
    ((:detectcolor __detectcolor) 0)
    ((:detect_done __detect_done) nil)
    ((:reportgoal __reportgoal) 0)
    ((:odometrie_1 __odometrie_1) (instance geometry_msgs::Pose2D :init))
    ((:odometrie_2 __odometrie_2) (instance geometry_msgs::Pose2D :init))
    )
   (send-super :init)
   (setq _abratio (float __abratio))
   (setq _detectcolor (round __detectcolor))
   (setq _detect_done __detect_done)
   (setq _reportgoal (round __reportgoal))
   (setq _odometrie_1 __odometrie_1)
   (setq _odometrie_2 __odometrie_2)
   self)
  (:abratio
   (&optional __abratio)
   (if __abratio (setq _abratio __abratio)) _abratio)
  (:detectcolor
   (&optional __detectcolor)
   (if __detectcolor (setq _detectcolor __detectcolor)) _detectcolor)
  (:detect_done
   (&optional __detect_done)
   (if __detect_done (setq _detect_done __detect_done)) _detect_done)
  (:reportgoal
   (&optional __reportgoal)
   (if __reportgoal (setq _reportgoal __reportgoal)) _reportgoal)
  (:odometrie_1
   (&rest __odometrie_1)
   (if (keywordp (car __odometrie_1))
       (send* _odometrie_1 __odometrie_1)
     (progn
       (if __odometrie_1 (setq _odometrie_1 (car __odometrie_1)))
       _odometrie_1)))
  (:odometrie_2
   (&rest __odometrie_2)
   (if (keywordp (car __odometrie_2))
       (send* _odometrie_2 __odometrie_2)
     (progn
       (if __odometrie_2 (setq _odometrie_2 (car __odometrie_2)))
       _odometrie_2)))
  (:serialization-length
   ()
   (+
    ;; float64 _abratio
    8
    ;; int8 _detectcolor
    1
    ;; bool _detect_done
    1
    ;; int8 _reportgoal
    1
    ;; geometry_msgs/Pose2D _odometrie_1
    (send _odometrie_1 :serialization-length)
    ;; geometry_msgs/Pose2D _odometrie_2
    (send _odometrie_2 :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _abratio
       (sys::poke _abratio (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; int8 _detectcolor
       (write-byte _detectcolor s)
     ;; bool _detect_done
       (if _detect_done (write-byte -1 s) (write-byte 0 s))
     ;; int8 _reportgoal
       (write-byte _reportgoal s)
     ;; geometry_msgs/Pose2D _odometrie_1
       (send _odometrie_1 :serialize s)
     ;; geometry_msgs/Pose2D _odometrie_2
       (send _odometrie_2 :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _abratio
     (setq _abratio (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; int8 _detectcolor
     (setq _detectcolor (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _detectcolor 127) (setq _detectcolor (- _detectcolor 256)))
   ;; bool _detect_done
     (setq _detect_done (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; int8 _reportgoal
     (setq _reportgoal (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _reportgoal 127) (setq _reportgoal (- _reportgoal 256)))
   ;; geometry_msgs/Pose2D _odometrie_1
     (send _odometrie_1 :deserialize buf ptr-) (incf ptr- (send _odometrie_1 :serialization-length))
   ;; geometry_msgs/Pose2D _odometrie_2
     (send _odometrie_2 :deserialize buf ptr-) (incf ptr- (send _odometrie_2 :serialization-length))
   ;;
   self)
  )

(setf (get robottest::signal_robot :md5sum-) "7edb32daa132df4f0725a8b5753c4c95")
(setf (get robottest::signal_robot :datatype-) "robottest/signal_robot")
(setf (get robottest::signal_robot :definition-)
      "float64               abratio      
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

")



(provide :robottest/signal_robot "7edb32daa132df4f0725a8b5753c4c95")


