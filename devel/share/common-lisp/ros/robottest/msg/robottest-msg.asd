
(cl:in-package :asdf)

(defsystem "robottest-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "signal_robot" :depends-on ("_package_signal_robot"))
    (:file "_package_signal_robot" :depends-on ("_package"))
    (:file "signal_transfer" :depends-on ("_package_signal_transfer"))
    (:file "_package_signal_transfer" :depends-on ("_package"))
  ))