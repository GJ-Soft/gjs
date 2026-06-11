# Project.py

import os
from pathlib import Path


class Project:

    @staticmethod
    def isTestEnvironment() -> bool :
        return os.environ.get('MAVEN_TEST_PHASE') == 'true'
 
