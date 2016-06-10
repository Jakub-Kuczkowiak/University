package com.januszsoft.bikerental.backend.dao;

import com.januszsoft.bikerental.backend.models.Bike;
import com.januszsoft.bikerental.backend.models.Station;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;

import javax.sql.DataSource;
import java.util.List;

public class StationDaoImpl implements Dao<Station> {

  private JdbcTemplate jdbcTemplate;

  public StationDaoImpl(DataSource dataSource) {
    jdbcTemplate = new JdbcTemplate(dataSource);
  }

  public void saveOrUpdate(Station station) {
    if (station.getId() != null && station.getId() > 0) {

      String sql_count = "SELECT COUNT * FROM bike b WHERE b.station = " + station.getId();
      int numberOfFreeSpaces = jdbcTemplate.queryForObject(sql_count, Integer.class);

      String sql = "UPDATE station SET service=?, address=?, numberoffreespaces=?, capacity=?,  latitude=?, longitude=?, numberoffreespaces WHERE id=?";

      jdbcTemplate.update(sql, station.getService(), station.getAddress(),
        numberOfFreeSpaces, station.getCapacity(), station.getLatitude(), station.getLongitude(), numberOfFreeSpaces, station.getId());
    } else {
      String sql = "INSERT INTO station (service, address, numberoffreespaces, capacity, latitude, longitude, numberoffreespaces) VALUES (?, ?, ?, ?, ?, ?, ?)";
      jdbcTemplate.update(sql, station.getService(), station.getAddress(),
        station.getNumberofreesapaces(), station.getCapacity(), station.getLatitude(), station.getLongitude(), station.getCapacity());
    }
  }

  @Override
  public void delete(Integer stationId) {
    String sql = "DELETE FROM station WHERE id=?";
    jdbcTemplate.update(sql, stationId);
  }

  @Override
  public Station get(Integer stationId) {

    String sql = "SELECT * FROM station WHERE id=" + stationId;
    List answer = jdbcTemplate.query(sql, new BeanPropertyRowMapper(Station.class));
    if (answer.size() == 0) return null;
    else return (Station) answer.get(0);

  }

  @Override
  public List<Station> findall() {
    String sql = "SELECT * FROM station";
    return jdbcTemplate.query(sql, new BeanPropertyRowMapper(Station.class));
  }

  public List<Bike> getListOfBikes(Integer stationID) {
    String sql = "SELECT * FROM bike WHERE station=" + stationID;
    return jdbcTemplate.query(sql, new BeanPropertyRowMapper(Bike.class));
  }

}

