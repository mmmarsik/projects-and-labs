class GameInfo:
    def __init__(self, caretakers: dict[int, str], admins: dict[int, str], stations: dict[str, bool]):
        self.caretakers = caretakers
        self.admins = admins
        self.stations = stations

    def is_station_free(self, station_name: str):
        return self.stations.get(station_name, False)

    def get_station_by_id(self, user_id: int):
        return self.caretakers.get(user_id) or self.admins.get(user_id)

    def set_station_status(self, station_name: str, is_free: bool):
        if station_name in self.stations:
            self.stations[station_name] = is_free

    def get_free_stations(self):
        return [station for station, is_free in self.stations.items() if is_free]
