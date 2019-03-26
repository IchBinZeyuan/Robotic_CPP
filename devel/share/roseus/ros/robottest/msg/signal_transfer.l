;; Auto-generated. Do not edit!


(when (boundp 'robottest::signal_transfer)
  (if (not (find-package "ROBOTTEST"))
    (make-package "ROBOTTEST"))
  (shadow 'signal_transfer (find-package "ROBOTTEST")))
(unless (find-package "ROBOTTEST::SIGNAL_TRANSFER")
  (make-package "ROBOTTEST::SIGNAL_TRANSFER"))

(in-package "ROS")
;;//! \htmlinclude signal_transfer.msg.html


(defclass robottest::signal_transfer
  :super ros::object
  :slots (_detectionstart _gamestart _stop _true_a _true_b _T_color ))

(defmethod robottest::signal_transfer
  (:init
   (&key
    ((:detectionstart __detectionstart) nil)
    ((:gamestart __gamestart) nil)
    ((:stop __stop) nil)
    ((:true_a __true_a) 0.0)
    ((:true_b __true_b) 0.0)
    ((:T_color __T_color) 0)
    )
   (send-super :init)
   (setq _detectionstart __detectionstart)
   (setq _gamestart __gamestart)
   (setq _stop __stop)
   (setq _true_a (float __true_a))
   (setq _true_b (float __true_b))
   (setq _T_color (round __T_color))
   self)
  (:detectionstart
   (&optional __detectionstart)
   (if __detectionstart (setq _detectionstart __detectionstart)) _detectionstart)
  (:gamestart
   (&optional __gamestart)
   (if __gamestart (setq _gamestart __gamestart)) _gamestart)
  (:stop
   (&optional __stop)
   (if __stop (setq _stop __stop)) _stop)
  (:true_a
   (&optional __true_a)
   (if __true_a (setq _true_a __true_a)) _true_a)
  (:true_b
   (&optional __true_b)
   (if __true_b (setq _true_b __true_b)) _true_b)
  (:T_color
   (&optional __T_color)
   (if __T_color (setq _T_color __T_color)) _T_color)
  (:serialization-length
   ()
   (+
    ;; bool _detectionstart
    1
    ;; bool _gamestart
    1
    ;; bool _stop
    1
    ;; float64 _true_a
    8
    ;; float64 _true_b
    8
    ;; int8 _T_color
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _detectionstart
       (if _detectionstart (write-byte -1 s) (write-byte 0 s))
     ;; bool _gamestart
       (if _gamestart (write-byte -1 s) (write-byte 0 s))
     ;; bool _stop
       (if _stop (write-byte -1 s) (write-byte 0 s))
     ;; float64 _true_a
       (sys::poke _true_a (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _true_b
       (sys::poke _true_b (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; int8 _T_color
       (write-byte _T_color s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _detectionstart
     (setq _detectionstart (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _gamestart
     (setq _gamestart (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _stop
     (setq _stop (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float64 _true_a
     (setq _true_a (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _true_b
     (setq _true_b (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; int8 _T_color
     (setq _T_color (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _T_color 127) (setq _T_color (- _T_color 256)))
   ;;
   self)
  )

(setf (get robottest::signal_transfer :md5sum-) "1b8d9240a4bf9c05c0ffc88fd32a8535")
(setf (get robottest::signal_transfer :datatype-) "robottest/signal_transfer")
(setf (get robottest::signal_transfer :definition-)
      " 
bool  detectionstart        # bool detect_start signal
bool  gamestart             # bool game_start signal
bool  stop                  # bool stop_signal
float64 true_a              # float default_a
float64 true_b              # float default_b
int8  T_color               # int8 default_color 0 yellow, 1 blue



")



(provide :robottest/signal_transfer "1b8d9240a4bf9c05c0ffc88fd32a8535")


