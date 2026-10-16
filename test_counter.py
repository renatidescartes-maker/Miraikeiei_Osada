import os
import subprocess
import pytest

def test_source_contains_required_components():
    assert os.path.exists("counter.c"), "counter.c does not exist"
    with open("counter.c", "r", encoding="utf-8") as f:
        content = f.read()

    assert "カウント" in content
    assert "リセット" in content
    assert "ID_BTN_COUNT" in content
    assert "ID_BTN_RESET" in content
    assert "wWinMain" in content

def test_executable_exists_and_is_windows_pe():
    exe_path = "counter.exe"
    assert os.path.exists(exe_path), "counter.exe does not exist"

    file_output = subprocess.check_output(["file", exe_path]).decode("utf-8")
    assert "PE32" in file_output
    assert "executable" in file_output
