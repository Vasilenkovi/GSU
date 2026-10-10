from conan import ConanFile
from conan.tools.scm import Git
from conan.tools.files import copy, rm
import os


class HDiffPatchConan(ConanFile):
    name = "hdiffpatch"
    version = "1.0.0"

    license = "MIT"
    author = "HDiffPatch contributors"
    url = "https://github.com/sisong/HDiffPatch"
    description = "Binary diff and patch library for large files"
    topics = ("diff", "patch", "binary", "delta")

    # Project compiles HDiffPatch sources directly, so we provide them as part of the package
    package_type = "application"

    def source(self):
        git = Git(self)
        git.clone(url="https://github.com/sisong/HDiffPatch.git", target=".")
        # Remove .git directory to avoid conflicts
        rm(self, os.path.join(self.source_folder, ".git"), "*", recursive=True)

    def package(self):
        # Copy entire repository preserving directory structure
        copy(self, "*", src=self.source_folder, dst=self.package_folder)

    def package_info(self):
        # For header-only usage, but we also provide sources
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
