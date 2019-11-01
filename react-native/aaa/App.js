/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * @format
 * @flow
 */

import React, {Component} from 'react';
import {Platform, StyleSheet, Text, View} from 'react-native';
import BackgroundTimer from 'react-native-background-timer';

const instructions = Platform.select({
  ios: 'Press Cmd+R to reload,\n' + 'Cmd+D or shake for dev menu',
  android:
    'Double tap R on your keyboard to reload,\n' +
    'Shake or press menu button for dev menu',
});

async function getCurrentPosition(timeoutMillis = 10000) {
  return new Promise((resolve, reject) => {
      navigator.geolocation.getCurrentPosition(resolve, reject, { timeout: timeoutMillis });
  });
}

type Props = {};
export default class App extends Component<Props> {
  constructor(props) {
    super(props);
    this.state = {
      coords: {
        latitude: 200,
        longitude: 300
      },
      last_post: {
        triangle_id: 0,
        date: 'no data'
      },
      counter: 0
    }
    this.setLocationPostTimer = this.setLocationPostTimer.bind(this);
    this.sendKokoLocation = this.sendKokoLocation.bind(this);
  }

  async componentDidMount() {
    this.sendKokoLocation();
    this.setLocationPostTimer();
  }

  async sendKokoLocation() {
    try {
      const position = await getCurrentPosition(5000);
      const { latitude, longitude } = position.coords;
      this.setState({
        coords: {
          latitude,
          longitude
        }
      });

      fetch('https://system-koko.appspot.com/api/v1/location/littlesmith/geo_location', {
        method: 'POST',
        credentials: 'include',
        headers: new Headers({
          'Content-Type': 'application/json'
        }),
        body: JSON.stringify({
          latitude: latitude,
          longitude: longitude,
          date: new Date()
        })
      }).then(response => response.json())
        .catch(error => console.error('Error:', error))
        .then(response => {
          if (response.result == 'ok') {
            this.setState({
              last_post: {
                triangle_id: response.data.triangle_id,
                date: response.data.date
              }
            });
          } else {
            console.log("post geo_location ng.");
          }
        });
    } catch(e) {
      alert(e.message)
    }
  }

  async postCurrentPosition() {
    try {
      const position = await getCurrentPosition(5000);
      const { latitude, longitude } = position.coords;
    } catch(e) {
      console.log(e.message);
    }
  }

  setLocationPostTimer() {
    BackgroundTimer.runBackgroundTimer(this.sendKokoLocation, 1000 * 5 * 60);
  }

  render() {
    return (
      <View style={styles.container}>
        <Text style={styles.instructions}>To get started, edit App</Text>
        <Text style={styles.instructions}>{this.state.counter}</Text>
        <Text style={styles.instructions}>{this.state.last_post.date}</Text>
        <Text style={styles.instructions}>{this.state.coords.latitude}</Text>
        <Text style={styles.instructions}>{this.state.coords.longitude}</Text>
      </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#F5FCFF',
  },
  welcome: {
    fontSize: 20,
    textAlign: 'center',
    margin: 10,
  },
  instructions: {
    textAlign: 'center',
    color: '#333333',
    marginBottom: 5,
  },
});
