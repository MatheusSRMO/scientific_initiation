import googlemaps
from datetime import datetime
import json


GOOGLE_API_KEY = "AIzaSyBIhbyHGnKi6upHuvlDL8OOexHh1f0Alw4"
gmaps = googlemaps.Client(key=GOOGLE_API_KEY)


def search_by_text(query, location):
    places = gmaps.places(query, location=location, radius=1000)
    places_dict = {}
    for place in places["results"]:
        places_dict[place["name"]] = {
            "address": place["formatted_address"],
            "location": place["geometry"]["location"],                              
        }
    return places_dict


if __name__ == "__main__":

    json_formated = json.dumps(
        search_by_text("a", "Jardim da Penha, Vitória, ES, Brasil"),
        indent=4,
        sort_keys=True
    )

    print(json_formated)
