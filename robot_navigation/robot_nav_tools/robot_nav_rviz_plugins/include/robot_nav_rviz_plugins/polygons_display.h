/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2020, Locus Robotics
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef ROBOT_NAV_RVIZ_PLUGINS_POLYGONS_DISPLAY_H
#define ROBOT_NAV_RVIZ_PLUGINS_POLYGONS_DISPLAY_H

#include <nav_2d_msgs/Polygon2DCollection.h>
#include <rviz/message_filter_display.h>
#include <rviz/properties/enum_property.h>
#include <rviz/properties/color_property.h>
#include <rviz/properties/float_property.h>
#include <robot_nav_rviz_plugins/polygon_parts.h>
#include <OgreManualObject.h>
#include <OgreMaterial.h>
#include <string>
#include <vector>

namespace robot_nav_rviz_plugins
{
/**
 * @brief Displays a nav_2d_msgs::Polygon2DCollection message in Rviz
 */
class PolygonsDisplay: public rviz::MessageFilterDisplay<nav_2d_msgs::Polygon2DCollection>
{
Q_OBJECT
public:
  PolygonsDisplay();
  virtual ~PolygonsDisplay();
  void reset() override;

protected:
  void processMessage(const nav_2d_msgs::Polygon2DCollection::ConstPtr& msg) override;
  void resetOutlines();
  void resetFillers();

private Q_SLOTS:
  void updateStyle();
  void updateProperties();

private:
  std::vector<nav_2d_msgs::Polygon2D> saved_outlines_;
  nav_2d_msgs::Polygon2DCollection saved_polygons_;

  std::vector<PolygonOutline*> outline_objects_;
  std::vector<PolygonFill*> filler_objects_;
  PolygonMaterial polygon_material_;

  PolygonDisplayModeProperty* mode_property_;
  rviz::FloatProperty* zoffset_property_;
  rviz::ColorProperty* outline_color_property_;
  rviz::ColorProperty* filler_color_property_;
  rviz::FloatProperty* filler_alpha_property_;

  enum struct FillColorMode {SINGLE, FROM_MSG, UNIQUE};
  FillColorMode getFillColorMode() const { return static_cast<FillColorMode>(color_mode_property_->getOptionInt()); }
  rviz::EnumProperty* color_mode_property_;

  std::vector<std_msgs::ColorRGBA> unique_colors_;
};
}  // namespace robot_nav_rviz_plugins

#endif  // ROBOT_NAV_RVIZ_PLUGINS_POLYGONS_DISPLAY_H