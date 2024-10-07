import ffmpeg
import subprocess
import multiprocessing

class Processer:
    pass

def merge_videos(input_files, output_file):
    input_args = "-c:v h264_qsv "
    for file in input_files:
        input_args += f"-i {file} "
    command = f"ffmpeg {input_args} -filter_complex concat=n={len(input_files)}:v=1:a=1 -f mp4 {output_file}"
    subprocess.run(command, shell=True)

# 输入视频文件路径和输出视频文件路径
input_file = './rt/4.mp4'
output_file_1 = './tmp/cl4.mp4'
output_file_2 = './tmp/cr4.mp4'

def cut_l(inf, ouf, rrr):
    command = f"ffmpeg -c:v h264_qsv -i {inf} -t {rrr} {ouf}"
    subprocess.run(command, shell=True)

def cut_r(inf, ouf, lll):
    command = f"ffmpeg -c:v h264_qsv -i {inf} -ss {lll} {ouf}"
    subprocess.run(command, shell=True)

if __name__ == "__main__":
    rrr = 145
    lll = 235
    
    # cut_l(input_file, output_file_1, rrr)
    # cut_r(input_file, output_file_2, lll)
    
    input_files = [output_file_1, output_file_2]  # 输入视频文件列表
    output_file = "./src/4_m.mp4"  # 输出合并后的视频文件名
    merge_videos(input_files, output_file)
