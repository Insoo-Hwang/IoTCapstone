# 객체 트래킹 하는 코드 o
# 구역 구분 라벨 o
# 순서대로 카운팅 o + id라벨 o
# 구역 바뀔 때만 출력 o
# 객체 인식 할때마다 가장 최근의 id로 받아와야함 :

import cv2
import io
import boto3
import pandas as pd

# 버킷의 어세스키와 시크릿키
s3 = boto3.client(
	's3',
	aws_access_key_id="AKIA5EZPEWGEHH4E5PH3",
	aws_secret_access_key="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",
)

# s3에서 파일 다운로드
file_name = 'test.txt'      # 다운될 이미지 이름
bucket = 'iotsend'           #버켓 주소
key = 'app/text' # s3 id 파일
#local_file = 'C:\Users\user\PycharmProjects\pythonProject1track.txt'
#obj_file = 'trackingtest2'
#s3.upload_file(local_file,bukcket_name, obj_file)

s3.download_file(bucket, key, file_name)

# 파일 내용 읽기 (ID)
f = open('D:/다운로드/test.txt', 'r')
line = f.readline()  # 새파일.txt의 가장 첫 번째 줄이 화면에 출력
print(line)
f.close()

# 파일에 저장하고 s3에 업로드
#f1 = open("C:\Users\user\PycharmProjects\pythonProject1track.txt",'a')
#f1.write()



# 트래킹 객체 리스트와 히스토그램 리스트 초기화
objects = []
histograms = []
previous_box = None

def select_roi(event, x, y, flags, param):
    global objects, histograms, count

    if event == cv2.EVENT_LBUTTONDOWN:
        # 새로운 객체 추가
        objects.append((x, y, 0, 0))
        # 새로운 객체의 히스토그램 계산
        roi = frame[y:y+10, x:x+10]  # 임시 roi
        hsv_roi = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)
        hist = cv2.calcHist([hsv_roi], [0], None, [16], [0, 180])
        hist = cv2.normalize(hist, hist, 0, 255, cv2.NORM_MINMAX)
        histograms.append(hist)

    elif event == cv2.EVENT_MOUSEMOVE and len(objects) > 0:
        # 드래그 중인 객체 업데이트
        # 객체 리스트에서 마지막으로 추가된 객체(objects[-1])를 가져옵니다.
        # 객체의 좌상단 모서리의 위치 (objects[-1][0], objects[-1][1])와 현재 좌표 (x, y)를 사용하여 객체의 새 위치를 계산
        # 새 위치 정보를 객체 리스트(objects)에 저장
        objects[-1] = (objects[-1][0], objects[-1][1], x - objects[-1][0], y - objects[-1][1])

    # 드래그가 끝난 객체 트래킹 시작
    #
    elif event == cv2.EVENT_LBUTTONUP and len(objects) > 0:
        # 객체의 위치 정보를 사용하여 프레임(frame)에서 객체의 ROI(Region of Interest)를 추출
        roi = frame[objects[-1][1]:objects[-1][1]+objects[-1][3], objects[-1][0]:objects[-1][0]+objects[-1][2]]
        #  이미지의 색상 채널(Hue)에 대한 히스토그램을 계산
        hsv_roi = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)
        histograms[-1] = cv2.calcHist([hsv_roi], [0], None, [16], [0, 180])
        histograms[-1] = cv2.normalize(histograms[-1], histograms[-1], 0, 255, cv2.NORM_MINMAX)
        # 트래커 객체
        tracker = cv2.TrackerKCF_create() # 생성
        tracker.init(frame, tuple(objects[-1])) # 초기화 , 위치와 크기 정보
        trackers.append(tracker)
        count += 1

    #count.append('1')

# 객체의 위치와 중심좌표를 비교하면 L 또는 R 을 반환하는 함수
def direction_box(box, center): # center_x >= frame.shape[1] / 2
    direction = ''
    x, y, w, h = box

    # calculate distance from center to left and right boundaries of the box
    distance_to_left = center[0] - x
    distance_to_right = x + w - center[0]
    center_x = frame.shape[1] // 2

    if center[0] < frame.shape[1] / 2:
        direction = 'L'
    elif center[0] >= frame.shape[1] / 2:
        direction = 'R'

    return direction

# 구역 바뀔 때마다 s3에 올릴 파일 저장
def file_save(cnt,id,dict):
    f1 = open("D:/다운로드/track.txt",'w')  # a는 값누적 w
    data = f"{line}{direction}"
    f1.write(data)
    f1.close()

def s3_save():
# s3에 업로드
    local_file = 'D:/다운로드/track.txt'
    obj_file = 'trackingtest2'
    s3.upload_file(local_file,bucket, obj_file)


# 카메라 캡처 객체 생성
cap = cv2.VideoCapture(0)

# 윈도우 생성 및 마우스 콜백 함수 설정v
cv2.namedWindow('frame')
cv2.setMouseCallback('frame', select_roi)
count =0

is_left = False  # 'l' 구역에 있는지 여부를 저장하는 변수
is_right = False  # 'r' 구역에 있는지 여부를 저장하는 변수

# 트래킹 시작
previous_box = None
trackers = []
while True:
    ret, frame = cap.read()

    # 모든 객체에 대해 트래킹 업데이트
    for i in range(len(trackers)):
        success, box = trackers[i].update(frame)
        #cv2.putText(frame, f"Count: {i}, ID:{label_id(box, i)}", (box[0] - 10, box[1] - 10), cv2.FONT_HERSHEY_SIMPLEX, 1,(0, 255, 0), 2)  # 트레킹 하는 동안 계속 출력
        #cv2.putText(frame, f"Count: {i}, ID:{line}", (box[0] - 10, box[1] - 10), cv2.FONT_HERSHEY_SIMPLEX,1, (0, 255, 0), 2)
        if success:
            box = [int(b) for b in box]
            p1 = (int(box[0]), int(box[1]))
            p2 = (int(box[0] + box[2]), int(box[1] + box[3]))
            cv2.rectangle(frame, p1, p2, (255,0,0), 2)
            center = (int(box[0] + box[2] / 2), int(box[1] + box[3] / 2))
            direction = direction_box(box, center)
            cv2.putText(frame, direction, (center[0] - 20, center[1] - 20), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
            cv2.putText(frame, f"Count: {i}, ID:{line}", (box[0] - 10, box[1] - 10), cv2.FONT_HERSHEY_SIMPLEX,
                        1, (0, 255, 0), 2)

            if direction == 'L':
                if not is_left:
                    print(f"{line}{direction}")
                    # 파일에 저장하고
                    file_save(i,line,direction)
                    s3_save()
                    is_left = True
                    is_right = False
            elif direction == 'R':
                if not is_right:
                    print(f"{line}{direction}")
                    file_save(i, line, direction)
                    s3_save()
                    is_left = False  # 'r' 구역에 있으므로 is_left 값을 False로 설정합니다.
                    is_right = True
            #cv2.putText(frame, f"Count: {count}", (box[0] - 10, box[1] - 10), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0),  2)
            #cv2.putText(frame, f"Count: {len(count)}", (box[0] - 10, box[1] - 10), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0),  2)
            #cnt = label_id(box,count)
            #cv2.putText(frame, cnt, (box[0] - 10, box[1] - 10), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
        else:
            del trackers[i], objects[i], histograms[i]


            # 파일에 저장하고
            #f1 = open("D:/다운로드/track.txt",'a')
            #data = f"Count: {i}, ID:{line}, Dict:{direction}"
            #f1.write(data)
            #f1.close()
            # s3에 업로드
            #local_file = 'D:/다운로드/track.txt'
            #obj_file = 'trackingtest2'
            #s3.upload_file(local_file,bucket, obj_file)


    #dst = cv2.flip(frame, 1)
    cv2.imshow('frame', frame)
    if cv2.waitKey(1)  == 27:
        break
    #if cv2.waitKey(1) & 0xFF == ord('q'):
    #    break

cap.release()
cv2.destroyAllWindows()
