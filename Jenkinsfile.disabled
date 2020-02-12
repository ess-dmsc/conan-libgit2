@Library('ecdc-pipeline')
import ecdcpipeline.ContainerBuildNode
import ecdcpipeline.ConanPackageBuilder

project = "conan-libgit2"

conan_user = "ess-dmsc"
conanPackageChannel = 'stable'

containerBuildNodes = [
  'centos': ContainerBuildNode.getDefaultContainerBuildNode('centos7'),
  'debian9': ContainerBuildNode.getDefaultContainerBuildNode('debian9'),
  'ubuntu1804': ContainerBuildNode.getDefaultContainerBuildNode('ubuntu1804'),
  'alpine': ContainerBuildNode.getDefaultContainerBuildNode('alpine')
]

packageBuilder = new ConanPackageBuilder(this, containerBuildNodes, conanPackageChannel)
packageBuilder.defineRemoteUploadNode('centos')

builders = packageBuilder.createPackageBuilders { container ->
  packageBuilder.addConfiguration(container)
}

def get_macos_pipeline() {
  return {
    node('macos') {
      cleanWs()
      dir("${project}") {
        stage("macOS: Checkout") {
          checkout scm
        }  // stage

        stage("macOS: Package") {
          sh "conan create . ${conan_user}/${conanPackageChannel} \
            --settings libgit2:build_type=Release \
            --options libgit2:shared=False \
            --build=outdated"

          sh "conan create . ${conan_user}/${conanPackageChannel} \
            --settings libgit2:build_type=Release \
            --options libgit2:shared=True \
            --build=outdated"
        }  // stage
      }  // dir
    }  // node
  }  // return
}  // def

def get_win10_pipeline() {
  return {
    node('windows10') {
      // Use custom location to avoid Win32 path length issues
      ws('c:\\jenkins\\') {
      cleanWs()
      dir("${project}") {
        stage("win10: Checkout") {
          checkout scm
        }  // stage

        stage("win10: Package") {
          bat """C:\\Users\\dmgroup\\AppData\\Local\\Programs\\Python\\Python36\\Scripts\\conan.exe \
            create . ${conan_user}/${conanPackageChannel} \
            --settings libgit2:build_type=Release \
            --options libgit2:shared=True \
            --build=outdated"""
        }  // stage
      }  // dir
      }  // ws
    }  // node
  }  // return
}  // def

node {
  checkout scm
  builders['macOS'] = get_macos_pipeline()
  builders['windows10'] = get_win10_pipeline()
  parallel builders
  cleanWs()
}
