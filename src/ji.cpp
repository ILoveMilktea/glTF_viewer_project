void set_transform()
{
  const std::vector<tinygltf::Node> &nodes = model.nodes;
  std::cout << model.cameras.size() << "\n";
  if (model.cameras.size() !=0)
  {
    const std::vector<tinygltf::Camera> &cameras = model.cameras;
    const tinygltf::Camera &camera = cameras[camera_index];
    if (camera.type.compare("perspective") == 0)
    {
      float fovy = kmuvcl::math::rad2deg(camera.perspective.yfov);
      float aspectRatio = camera.perspective.aspectRatio;
      float znear = camera.perspective.znear;
      float zfar = camera.perspective.zfar;
      zfar += 10000;

      std::cout << "(camera.mode() == Camera::kPerspective)" << std::endl;
      std::cout << "(fovy, aspect, n, f): " << fovy << ", " << aspectRatio << ", " << znear << ", " << zfar << std::endl;
      mat_proj = kmuvcl::math::perspective(fovy, aspectRatio, znear, zfar);
    }
    else // (camera.type.compare("orthographic") == 0)
    {
      float xmag = camera.orthographic.xmag;
      float ymag = camera.orthographic.ymag;
      float znear = camera.orthographic.znear;
      float zfar = camera.orthographic.zfar;

      std::cout << "(camera.mode() == Camera::kOrtho)" << std::endl;
      std::cout << "(xmag, ymag, n, f): " << xmag << ", " << ymag << ", " << znear << ", " << zfar << std::endl;
      mat_proj = kmuvcl::math::ortho(-xmag, xmag, -ymag, ymag, znear, zfar);
    }
  }
  else
  {
    mat_view.set_to_identity();

    mat_proj.set_to_identity();
    float fovy = 70.0f;
    float aspectRatio = 1.0f;
    float znear = 0.01f;
    float zfar = 100.0f;

    mat_proj = kmuvcl::math::perspective(fovy, aspectRatio, znear, zfar);
    // mat_view = kmuvcl::math::translate(0.0f, -1.0f,-2.5f);
    // std::cout << "else\n";
  }

  for (const tinygltf::Node &node : nodes)
  {
    // mat_view = kmuvcl::math::translate(0.0f, 0.0f, 0.0f);
    // std::cout << "scale " << node.scale.size() << " rota " << node.rotation.size() << " trans " << node.translation.size() << "\n";
    if (node.camera == camera_index)
    {
      mat_view = kmuvcl::math::translate(0.0f, -1.0f, -5.0f);

      if (node.scale.size() == 3)
      {
        mat_view = mat_view * kmuvcl::math::scale<float>(
                                  1.0f / node.scale[0], 1.0f / node.scale[1], 1.0f / node.scale[2]);
      }

      if (node.rotation.size() == 4)
      {
        mat_view = mat_view * kmuvcl::math::quat2mat(
                                  node.rotation[0], node.rotation[1], node.rotation[2], node.rotation[3])
                                  .transpose();
      }

      if (node.translation.size() == 3)
      {
        mat_view = mat_view * kmuvcl::math::translate<float>(
                                  -node.translation[0], -node.translation[1], -node.translation[2]);
      }
    }
  }
}
