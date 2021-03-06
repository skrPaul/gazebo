/*
 * Copyright (C) 2018 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#ifndef GAZEBO_PLUGINS_KEYSTOCMDVELPLUGIN_HH_
#define GAZEBO_PLUGINS_KEYSTOCMDVELPLUGIN_HH_

#include <memory>
#include <string>
#include <vector>
#include <ignition/transport/Node.hh>

#include <gazebo/common/Plugin.hh>
#include <gazebo/transport/Node.hh>

namespace gazebo
{
  class CmdVelKeyboardControls;
  class KeysToCmdVelPluginPrivate;

  /// \brief Send velocity commands to a model based on keypress messages
  ///        received.
  ///
  /// The commands are instances of Pose type with x field denoting linear speed
  /// and yaw denoting angular speed.
  ///
  /// The keypresses are taken from topic "~/keyboard/keypress" generated by the
  /// KeyboardGUIPlugin.
  ///
  /// Unfortunately, due to the implementation of the KeyboardGUIPlugin, this
  /// plugin can only process the "key down" events and not "key up" events, so
  /// it is not possible to react on the set of keys currently pressed, but only
  /// to a sequence of keypresses.
  ///
  /// The plugin processes the following parameters:
  ///
  /// <publish_as_twist> If true, the published message type will be Twist.
  ///                    If false, it will be Pose. Default is false.
  ///                    The Pose message isn't very good for angular speed
  ///                    representation since it will always clamp the speed to
  ///                    interval -pi to pi.
  /// <cmd_vel_topic>  The topic to which velocity commands are be published.
  ///                  Default is "~/cmd_vel".
  /// <max_linear_vel>  Maximum linear velocity commanded to the vehicle (m/s).
  ///                   Default is 1.0 (m/s).
  /// <min_linear_vel>  Minimum linear velocity commanded to the vehicle (m/s).
  ///                   Default is -max_linear_vel (m/s).
  /// <max_angular_vel>  Maximum angular velocity commanded to the
  ///                    vehicle (rad/s).
  ///                    Default is 1.0 (rad/s).
  /// <key_controls>  If this tag is empty or missing, the default assignment
  ///                 (arrow keys) is used; otherwise, the keys can be set using
  ///                 the (repeatable) subelements <stop>, <accelerate>,
  ///                 <decelerate>, <left> and <right> containing the keycodes.

class GZ_PLUGIN_VISIBLE KeysToCmdVelPlugin : public ModelPlugin
  {
    /// \brief Constructor.
    public: KeysToCmdVelPlugin();

    /// \brief Destructor
    public: ~KeysToCmdVelPlugin();

    // Documentation inherited
    public: void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf) override;

    // Documentation inherited
    public: void Init() override;

    // Documentation inherited
    public: void Reset() override;

    /// \brief Callback each time a key message is received.
    /// \param[in] _msg Keypress message.
    protected: virtual void OnKeyPress(ConstAnyPtr &_msg);

    /// \internal
    /// \brief Private data pointer.
    private: std::unique_ptr<KeysToCmdVelPluginPrivate> dataPtr;
  };
}
#endif
