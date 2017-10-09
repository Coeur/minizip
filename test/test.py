import os
import sys
import stat
import argparse
import json
import glob
import shutil
import fnmatch
import re
import pprint
import hashlib
from sys import platform

parser = argparse.ArgumentParser(description='Test script')
parser.add_argument('--exe_dir', help='Built exes directory', default=None, action='store', required=False)
args, unknown = parser.parse_known_args()

def hash_file_sha1(path):
    sha1 = hashlib.sha1()
    with open(path, 'rb') as f:
        while True:
            data = f.read(8192)
            if not data:
                break
            sha1.update(data)
    return sha1.hexdigest()

def erase_file(path):
    if os.path.exists(path):
        os.remove(path)
def erase_dir(path):
    if os.path.exists(path):
        shutil.rmtree(path)

def get_exec(name):
    global args
    if platform == 'win32':
        name += '.exe'
    if args.exe_dir is not None:
        return os.path.join(args.exe_dir, name)
    return name

def get_files_info(path):
    if os.path.isfile(path):
        return {
            path: {
                'hash': hash_file_sha1(path),
                'size': os.path.getsize(path)
            }
        }
    info = {}
    for root, dirs, files in os.walk(path):
        path = root.split(os.sep)
        for path in files:
            info.update(get_files_info(path))
    return info

def zip_unzip_test(zip_file, dest_dir, zip_args, unzip_args, files):
    # Single test run
    original_infos = {}
    for (i, path) in enumerate(files):
        original_infos.update(get_files_info(path))
    print original_infos

    erase_file(zip_file)
    erase_dir(dest_dir)

    cmd = '{0} {1} {2} {3}'.format(get_exec('minizip'), zip_args, zip_file, ' '.join(files))
    print cmd
    err = os.system(cmd)
    if (err != 0):
        print('Zip returned error code {0}'.format(err))
        exit(err)
    cmd = '{0} -l {1}'.format(get_exec('miniunz'), zip_file)
    print cmd
    err = os.system(cmd)
    if (err != 0):
        print('List returned error code {0}'.format(err))
        exit(err)
    cmd = '{0} -x {1} {2} -d {3}'.format(get_exec('miniunz'), zip_file, unzip_args, dest_dir)
    print cmd
    err = os.system(cmd)
    if (err != 0):
        print('Unzip returned error code {0}'.format(err))
        exit(err)

    new_infos = {}
    for (i, path) in enumerate(files):
        new_infos.update(get_files_info(path))

    if (' '.join(original_infos) != ' '.join(new_infos)):
        print('Infos do not match')
        print('Original: ')
        pprint(original_infos)
        print('New: ')
        print(new_infos)

def test_level_0(method, zip_arg = '', unzip_arg = ''):
    # File tests
    print 'Testing {0} on Single File'.format(method)
    zip_unzip_test('test.zip', 'out', zip_arg, unzip_arg, ['LICENSE'])
    print 'Testing {0} on Two Files'.format(method)
    zip_unzip_test('test.zip', 'out', zip_arg, unzip_arg, ['LICENSE', 'test.png'])
    print 'Testing {0} Directory'.format(method)
    zip_unzip_test('test.zip', 'out', zip_arg, unzip_arg, ['repo'])

def test_level_1(method = '', zip_arg = '', unzip_arg = ''):
    # Compression method tests
    method = method + ' ' if method != '' else ''
    test_level_0(method + 'Deflate', zip_arg, unzip_arg)
    test_level_0(method + 'Raw', '-0 ' + zip_arg, unzip_arg)
    test_level_0(method + 'BZIP2', '-b ' + zip_arg, unzip_arg)
    test_level_0(method + 'LZMA', '-l ' + zip_arg, unzip_arg)

if not os.path.exists('repo'):
    os.system('git clone https://github.com/nmoinvaz/minizip repo')

# Run tests
test_level_1()
test_level_1('Crypt', '-p 1234567890', '-p 1234567890')
test_level_1('AES', '-s -p 1234567890', '-p 1234567890')
