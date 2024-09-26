import numpy as np
import cv2
import tensorflow as tf
import pandas as pd
import logging

# 设置日志记录
logging.basicConfig(filename='tracker_log.txt', level=logging.INFO)

class KalmanFilter:
    def __init__(self):
        self.state = np.zeros((4, 1))
        self.P = np.eye(4)
        self.F = np.array([[1, 0, 1, 0], [0, 1, 0, 1], [0, 0, 1, 0], [0, 0, 0, 1]])
        self.Q = np.eye(4) * 0.01
        self.H = np.array([[1, 0, 0, 0], [0, 1, 0, 0]])
        self.R = np.eye(2) * 5

    def predict(self):
        self.state = self.F @ self.state
        self.P = self.F @ self.P @ self.F.T + self.Q

    def update(self, measurement):
        y = measurement - (self.H @ self.state)
        S = self.H @ self.P @ self.H.T + self.R
        K = self.P @ self.H.T @ np.linalg.inv(S)
        
        self.state = self.state + K @ y
        self.P = (np.eye(4) - K @ self.H) @ self.P

    def get_state(self):
        return self.state


class TargetTracker:
    def __init__(self, radar_data, infrared_data):
        self.radar_data = radar_data
        self.infrared_data = infrared_data
        self.tracked_targets = []
        self.kf = KalmanFilter()

    def preprocess_data(self):
        radar_processed = self._process_radar_data(self.radar_data)
        infrared_processed = self._process_infrared_data(self.infrared_data)
        return radar_processed, infrared_processed

    def _process_radar_data(self, data):
        return np.clip(data / np.max(data), 0, 1)

    def _process_infrared_data(self, data):
        return cv2.GaussianBlur(data, (5, 5), 0)

    def identify_targets(self, infrared_processed):
        targets = self._detect_targets(infrared_processed)
        self.tracked_targets = targets
        return targets

    def _detect_targets(self, infrared_image):
        model = tf.keras.applications.MobileNetV2(weights='imagenet', include_top=False, input_shape=(224, 224, 3))
        infrared_resized = cv2.resize(infrared_image, (224, 224))
        infrared_resized = np.expand_dims(infrared_resized, axis=0) / 255.0
        features = model.predict(infrared_resized)

        return self._post_process_detections(features)

    def _post_process_detections(self, features):
        return []  # 返回识别到的目标的轮廓或位置

    def track_targets(self):
        for target in self.tracked_targets:
            measurement = self._get_measurement(target)
            self.kf.predict()
            self.kf.update(measurement)

    def _get_measurement(self, target):
        x, y = target  # 假设目标包含（x, y）位置
        return np.array([[x], [y]])

    def save_to_csv(self, filename, targets):
        df = pd.DataFrame(targets, columns=["Target_X", "Target_Y"])
        try:
            df.to_csv(filename, index=False)
            logging.info(f'Successfully saved targets to {filename}.')
        except Exception as e:
            logging.error(f'Error saving to CSV: {e}')
            raise

    def run(self):
        try:
            radar_processed, infrared_processed = self.preprocess_data()
            targets = self.identify_targets(infrared_processed)
            self.track_targets()
            self.save_to_csv("tracked_targets.csv", targets)
            return targets
        except Exception as e:
            logging.error(f'Error running TargetTracker: {e}')
            raise

if __name__ == "__main__":
    radar_data = np.random.rand(100, 100)
    infrared_data = np.random.randint(0, 256, (100, 100)).astype(np.uint8)

    tracker = TargetTracker(radar_data, infrared_data)
    identified_targets = tracker.run()

    print(f"Identified {len(identified_targets)} targets.")
