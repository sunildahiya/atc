def my_range(start, end, step):
    while start <= end:
        yield start
        start += step

# if cv2.waitKey(1) & 0xFF == ord('q'):
#     break