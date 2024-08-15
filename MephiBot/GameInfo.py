class GameInfo:
    def __init__(self, caretakers: dict[int, str], admins: dict[int, str], stations_list: set[str], teams: set[str]):
        self.caretakers = caretakers
        self.admins = admins
        self.stations_list = stations_list
        self.teams = teams
        self.non_visited_list: dict[str, set[str]] = {}
        self.stations_status: dict[str, str] = {}
        self.team_on_station: dict[str, str] = {}  

        for team in teams:
            self.non_visited_list[team] = stations_list.copy()  

        for station in stations_list:
            self.stations_status[station] = "free"
            self.team_on_station[station] = None  


    def is_station_free(self, station_name: str):
        return self.stations_status.get(station_name) == "free"

    def is_station_in_progress(self, station_name: str):
        return self.stations_status.get(station_name) == "in_progress"

    def get_station_by_id(self, user_id: int):
        return self.caretakers.get(user_id)

    def get_id_by_station(self, station_name: str):
        for user_id, user_station in self.caretakers.items():
            if user_station == station_name:
                return user_id
        return None

    def set_station_status(self, station_name: str, status: str):
        if station_name in self.stations_status:
            self.stations_status[station_name] = status

    def lock_station(self, station_name: str, team_name: str):
        self.set_station_status(station_name, "busy")
        self.team_on_station[station_name] = team_name  


    def start_station_progress(self, station_name: str):
        self.set_station_status(station_name, "in_progress")
         

    def free_station(self, station_name: str):
        self.set_station_status(station_name, "free")
        self.team_on_station[station_name] = None  

    def get_next_free_station(self, team_name: str):
        team_stations: set = self.non_visited_list[team_name]

        print(f"abra {team_stations}")
        
        print()

        for station_name in team_stations:
            print(f"pum pum {station_name}")
            if self.is_station_free(station_name):
                next_free_station = station_name
                self.non_visited_list[team_name].remove(station_name)
                return next_free_station
        return None

    def get_team_by_station(self, station_name: str):
        return self.team_on_station[station_name]

    def get_station_by_team(self, team_name: str):
        for station, team in self.team_on_station.items():
            if team == team_name:
                return station
        return None
    
    def add_team(self, team_name: str):
        self.teams.add(team_name)
        self.non_visited_list[team_name] = self.stations_list.copy() 
        
