#include <cstdlib>
#include <iostream>
#include "git2.h"

int main()
{
    int versionMajor, versionMinor, versionRev;
    git_libgit2_version(&versionMajor, &versionMinor, &versionRev);

    std::cout << "libgit2 v" << versionMajor << "." << versionMinor << "." << versionRev << std::endl;

    std::cout << "Compile Features:" << std::endl;

    int features = git_libgit2_features();

    if (features & GIT_FEATURE_THREADS)
        std::cout << " - Thread safe" << std::endl;
    else
        std::cout << " - Single thread only" << std::endl;

    if (features & GIT_FEATURE_HTTPS)
        std::cout << " - HTTPS (OpenSSL)" << std::endl;
    else
        std::cout << " - No HTTPS support" << std::endl;

    if (features & GIT_FEATURE_SSH)
        std::cout << " - SSH (libssh2)" << std::endl;
    else
        std::cout << " - No SSH support" << std::endl;

    return EXIT_SUCCESS;
}
